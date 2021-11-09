#!/bin/bash
if [ "$(id -u)" -ne "0" ]
then
    echo
    echo "This script needs to be run as root, e.g.:"
    echo "sudo configure_usbfs.sh"
    echo
    exit 0
fi

RCLOCAL_PATH="/etc/rc.local"

USBFS_DEFAULT_VALUE=1000
USBFS_COMMAND="sh -c 'echo $USBFS_DEFAULT_VALUE > /sys/module/usbcore/parameters/usbfs_memory_mb'"
USBFS_COMMAND_PATTERN="(sh -c 'echo )([0-9]+)( > \/sys\/module\/usbcore\/parameters\/usbfs_memory_mb')"

MY_YESNO_PROMPT='[y/n] $ '

DEFAULT_RCLOCAL=$(cat <<-END
#!/bin/sh -e
#
# rc.local
#
# This script is executed at the end of each multiuser runlevel.
# Make sure that the script will "exit 0" on success or any other
# value on error.
#
# In order to enable or disable this script just change the execution
# bits.
#
# By default this script does nothing.

sh -c 'echo $USBFS_DEFAULT_VALUE > /sys/module/usbcore/parameters/usbfs_memory_mb'

exit 0

END
)

echo # Newline

# Check if rc.local exists
if [ -f "$RCLOCAL_PATH" ]
then
    # If the command doesn't already exist in rc.local, insert it.
    #   egrep, grep -E         interpret pattern as an extended regular expression
    #   -q, --quiet, --silent  do not write to stdout and exit immediately with status 0 if any match is found
    egrep -q "$USBFS_COMMAND_PATTERN" "$RCLOCAL_PATH"
    if [ $? -eq 0 ]
    then # Command already exists

        # Count number of occurrences of command
        if [ $(egrep "$USBFS_COMMAND_PATTERN" "$RCLOCAL_PATH" | wc --lines) -eq 1 ]
        then
            USBFS_EXISTING_VALUE=$(egrep "$USBFS_COMMAND_PATTERN" "$RCLOCAL_PATH" | sed -r "s/[ ]*$USBFS_COMMAND_PATTERN/\2/")

            # Memory is already >= the recommended value?
            if [ $USBFS_EXISTING_VALUE -ge $USBFS_DEFAULT_VALUE ]
            then
                echo "USB-FS memory is already set to $USBFS_EXISTING_VALUE MB which is greater than or equal to the recommended value of $USBFS_DEFAULT_VALUE MB."
                echo "No changes were made."
            else
                echo "Found an existing USB-FS memory configuration (currently $USBFS_EXISTING_VALUE MB)."
                echo "Would you like to change this to $USBFS_DEFAULT_VALUE MB?"

                echo -n "$MY_YESNO_PROMPT"
                read confirm
                if ( [ "$confirm" = "y" ] || [ "$confirm" = "Y" ] || [ "$confirm" = "yes" ] || [ "$confirm" = "Yes" ] || [ "$confirm" = "" ] )
                then
                    # -i modifies the file and creates a backup, -r enables extended regex, -n suppresses output
                    sudo sed -i.backup -r "s/$USBFS_COMMAND_PATTERN/\1$USBFS_DEFAULT_VALUE\3/" "$RCLOCAL_PATH"
                    echo "Changed USB-FS memory to $USBFS_DEFAULT_VALUE MB and created $RCLOCAL_PATH.backup."
                else
                    echo "No changes were made."
                fi
            fi
        else # If there is more than one occurrence, notify to update manually to avoid breaking things
            echo "Found more than one occurrence of the USB-FS memory configuration command in /etc/rc.local."
            echo "Please consult the 'USB notes' section in the included README for manual configuration instructions."
        fi
    else # Command doesn't exist in rc.local yet
        # If there exists an `exit 0` in rc.local, insert command before the last occurrence
        grep -Fxq "exit 0" "$RCLOCAL_PATH"
        if [ $? -eq 0 ]
        then
            # Get last 'exit 0' in format `<line #>:exit 0`
            #     -n, --line-number  prefix each line with 1-based line number
            USBFS_GREP_LAST_EXIT=$(grep -nFx "exit 0" "$RCLOCAL_PATH" | tail -1)

            # Strip text after colon
            USBFS_EXIT_LINE=${USBFS_GREP_LAST_EXIT%:*}

            # Insert usbfs command right before the `exit 0`
            sudo sed -i.backup -r "${USBFS_EXIT_LINE}i ${USBFS_COMMAND}" "$RCLOCAL_PATH"
        else # Otherwise, append command to end of file
            sudo sed -i.backup -r "\$a${USBFS_COMMAND}\nexit 0" "$RCLOCAL_PATH"
        fi
        echo "Set USB-FS memory to $USBFS_DEFAULT_VALUE MB and created $RCLOCAL_PATH.backup."
    fi
else
    # Using tee to redirect standard output with superuser rights
    echo "$DEFAULT_RCLOCAL" | sudo tee --append "$RCLOCAL_PATH" >/dev/null
    sudo chmod 744 "$RCLOCAL_PATH"
    echo "Created /etc/rc.local and set USB-FS memory to $USBFS_DEFAULT_VALUE MB."
fi

# Check if owner group has execute permissions
stat -c "%a" "$RCLOCAL_PATH" | egrep -q "[1|3|5|7][0-7][0-7]"
if [ $? -eq 1 ]
then
    echo
    echo "The /etc/rc.local file may not be able to run with its current"
    echo -n "permissions ("
    echo -n $(stat -c "%A" "$RCLOCAL_PATH")
    echo "). Set recommended (-rwxr--r--) permissions?"

    echo -n "$MY_YESNO_PROMPT"
    read confirm
    if ( [ "$confirm" = "y" ] || [ "$confirm" = "Y" ] || [ "$confirm" = "yes" ] || [ "$confirm" = "Yes" ] || [ "$confirm" = "" ] )
    then
        sudo chmod 744 "$RCLOCAL_PATH"
        echo "Changed $RCLOCAL_PATH permissions to 744."
    else
        echo "No changes were made. You may have to manually run 'sudo chmod 744 $RCLOCAL_PATH'."
    fi
fi

exit 0
