#!/bin/bash

set -o errexit

MY_PROMPT='$ '
MY_YESNO_PROMPT='[Y/n] $ '

grpname="flirimaging"

if [ "$(id -u)" = "0" ]
then
    echo
    echo "This script will assist users in configuring their udev rules to allow"
    echo "access to USB devices. The script will create a udev rule which will"
    echo "add FLIR USB devices to a group called $grpname. The user may also"
    echo "choose to restart the udev daemon. All of this can be done manually as well."
    echo
else
    echo
    echo "This script needs to be run as root, e.g.:"
    echo "sudo configure_spinnaker.sh"
    echo
    exit 0
fi

echo "Adding new members to usergroup $grpname..." 
while :
do
    # Show current members of the user group
    users=$(grep -E '^'$grpname':' /etc/group |sed -e 's/^.*://' |sed -e 's/, */, /g')
    if [ -z "$users" ]
    then 
        echo "Usergroup $grpname is empty"
    else
        echo "Current members of $grpname group: $users"
    fi

    echo "To add a new member please enter username (or hit Enter to continue):"
    echo -n "$MY_PROMPT"
    read usrname
    if [ "$usrname" = "" ]
    then
        break
    else
        # Check if user name exists
        if (getent passwd $usrname > /dev/null)
        then
            # Get confirmation that the username is ok 
            echo "Adding user $usrname to group $grpname group. Is this OK?"
            echo -n "$MY_YESNO_PROMPT"
            read confirm
            if [ "$confirm" = "y" ] || [ "$confirm" = "Y" ] || [ "$confirm" = "yes" ] || [ "$confirm" = "Yes" ] || [ "$confirm" = "" ]
            then
                # Create user group (if not exists) and add user to it
                groupadd -f $grpname
                usermod -a -G $grpname $usrname
                echo "Added user $usrname"
            fi
        else
            echo "User "\""$usrname"\"" does not exist"
        fi
    fi
done

# Create udev rule
UdevFile="/etc/udev/rules.d/40-flir-spinnaker.rules"
echo
echo "Writing the udev rules file...";
echo "SUBSYSTEM==\"usb\", ATTRS{idVendor}==\"1e10\", GROUP=\"$grpname\"" 1>>$UdevFile

echo "Do you want to restart the udev daemon?"
echo -n "$MY_YESNO_PROMPT"
read confirm
if [ "$confirm" = "y" ] || [ "$confirm" = "Y" ] || [ "$confirm" = "yes" ] || [ "$confirm" = "Yes" ] || [ "$confirm" = "" ]
then
    /etc/init.d/udev restart
else
    echo "Udev was not restarted.  Please reboot the computer for the rules to take effect."
    exit 0
fi

echo "Configuration complete."
echo "A reboot may be required on some systems for changes to take effect."
exit 0
