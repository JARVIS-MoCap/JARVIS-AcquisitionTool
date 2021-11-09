//=============================================================================
// Copyright (c) 2001-2020 FLIR Systems, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
   
/* Auto-generated file. Do not modify. */

#ifndef FLIR_SPINNAKER_CAMERA_H
#define FLIR_SPINNAKER_CAMERA_H

#include "SpinnakerPlatform.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include "CameraBase.h"
#include "CameraDefs.h"

namespace Spinnaker
{
    /**
    * @defgroup SpinnakerClasses Spinnaker Classes
    */
    /*@{*/

    /**
    * @defgroup Camera_h Camera Class
    */
    /*@{*/

    /**
    *@brief The camera object class.
    */

    class SPINNAKER_API Camera : public CameraBase
    {
    public:
        ~Camera();

        void Init();

    protected:
        Camera();
    private:
        Camera(const Camera &);
        Camera& operator=(const Camera&);

    public:
        /**
         * Description: 
      Control the index (offset) of the coefficient to access in the 
      selected LUT.
    
         * Visibility: 
         */
        GenApi::IInteger &LUTIndex;

        /**
         * Description: 
      Activates the selected LUT.
    
         * Visibility: 
         */
        GenApi::IBoolean &LUTEnable;

        /**
         * Description: 
      Returns the Value at entry LUTIndex of the LUT selected by LUTSelector.
    
         * Visibility: 
         */
        GenApi::IInteger &LUTValue;

        /**
         * Description: 
      Selects which LUT to control.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<LUTSelectorEnums> &LUTSelector;

        /**
         * Description: 
      Exposure time in microseconds when Exposure Mode is Timed.
    
         * Visibility: 
         */
        GenApi::IFloat &ExposureTime;

        /**
         * Description: This command stops the acquisition of images.
         * Visibility: 
         */
        GenApi::ICommand &AcquisitionStop;

        /**
         * Description: Resulting frame rate in Hertz. If this does not equal the Acquisition Frame Rate it is because the Exposure Time is greater than the frame time. 
         * Visibility: 
         */
        GenApi::IFloat &AcquisitionResultingFrameRate;

        /**
         * Description: Controls the rate (in Hertz) at which the Lines in a Frame are captured.
         * Visibility: 
         */
        GenApi::IFloat &AcquisitionLineRate;

        /**
         * Description: This command starts the acquisition of images.
         * Visibility: 
         */
        GenApi::ICommand &AcquisitionStart;

        /**
         * Description: 
      Generates an internal trigger if Trigger Source is set to Software.
    
         * Visibility: 
         */
        GenApi::ICommand &TriggerSoftware;

        /**
         * Description: 
      Sets the operation mode of the Exposure.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<ExposureModeEnums> &ExposureMode;

        /**
         * Description: Sets the acquisition mode of the device. Continuous: acquires images continuously. Multi Frame: acquires a specified number of images before stopping acquisition. Single Frame: acquires 1 image before stopping acquisition. 
         * Visibility: 
         */
        GenApi::IEnumerationT<AcquisitionModeEnums> &AcquisitionMode;

        /**
         * Description: 
      Number of images to acquire during a multi frame acquisition.
    
         * Visibility: 
         */
        GenApi::IInteger &AcquisitionFrameCount;

        /**
         * Description: 
      Specifies the internal signal or physical input line to use as the 
      trigger source. 
    
         * Visibility: 
         */
        GenApi::IEnumerationT<TriggerSourceEnums> &TriggerSource;

        /**
         * Description: Specifies the activation mode of the trigger.
         * Visibility: 
         */
        GenApi::IEnumerationT<TriggerActivationEnums> &TriggerActivation;

        /**
         * Description: Sets the shutter mode of the device.
         * Visibility: 
         */
        GenApi::IEnumerationT<SensorShutterModeEnums> &SensorShutterMode;

        /**
         * Description: 
      Specifies the delay in microseconds (us) to apply after the trigger
      reception before activating it.
    
         * Visibility: 
         */
        GenApi::IFloat &TriggerDelay;

        /**
         * Description: 
      Controls whether or not trigger is active.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<TriggerModeEnums> &TriggerMode;

        /**
         * Description: User controlled acquisition frame rate in Hertz
         * Visibility: 
         */
        GenApi::IFloat &AcquisitionFrameRate;

        /**
         * Description: Specifies the overlap mode of the trigger.
         * Visibility: 
         */
        GenApi::IEnumerationT<TriggerOverlapEnums> &TriggerOverlap;

        /**
         * Description: Selects the type of trigger to configure.
         * Visibility: 
         */
        GenApi::IEnumerationT<TriggerSelectorEnums> &TriggerSelector;

        /**
         * Description: If enabled, AcquisitionFrameRate can be used to manually control the frame rate.
         * Visibility: 
         */
        GenApi::IBoolean &AcquisitionFrameRateEnable;

        /**
         * Description: Sets the automatic exposure mode
         * Visibility: 
         */
        GenApi::IEnumerationT<ExposureAutoEnums> &ExposureAuto;

        /**
         * Description: 
      This feature is used only if the FrameBurstStart trigger is enabled and
      the FrameBurstEnd trigger is disabled. Note that the total number of
      frames captured is also conditioned by AcquisitionFrameCount if
      AcquisitionMode is MultiFrame and ignored if AcquisitionMode is Single. 
    
         * Visibility: 
         */
        GenApi::IInteger &AcquisitionBurstFrameCount;

        /**
         * Description: Returns the unique identifier of the Test type of Event.
         * Visibility: 
         */
        GenApi::IInteger &EventTest;

        /**
         * Description: Returns the Timestamp of the Test Event.
         * Visibility: 
         */
        GenApi::IInteger &EventTestTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Exposure End Event.
         * Visibility: 
         */
        GenApi::IInteger &EventExposureEndFrameID;

        /**
         * Description: Returns the unique identifier of the Exposure End type of Event.
         * Visibility: 
         */
        GenApi::IInteger &EventExposureEnd;

        /**
         * Description: Returns the Timestamp of the Exposure End Event.
         * Visibility: 
         */
        GenApi::IInteger &EventExposureEndTimestamp;

        /**
         * Description: Returns the unique identifier of the Error type of Event.
         * Visibility: 
         */
        GenApi::IInteger &EventError;

        /**
         * Description: Returns the Timestamp of the Error Event.
         * Visibility: 
         */
        GenApi::IInteger &EventErrorTimestamp;

        /**
         * Description: Returns the error code for the error that happened
         * Visibility: 
         */
        GenApi::IInteger &EventErrorCode;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Error Event.
         * Visibility: 
         */
        GenApi::IInteger &EventErrorFrameID;

        /**
         * Description: Selects which Event to enable or disable.
         * Visibility: 
         */
        GenApi::IEnumerationT<EventSelectorEnums> &EventSelector;

        /**
         * Description: Returns the status of the event serial receive overflow.
         * Visibility: 
         */
        GenApi::IBoolean &EventSerialReceiveOverflow;

        /**
         * Description: Returns the unique identifier of the Serial Port Receive type of Event.
         * Visibility: 
         */
        GenApi::IInteger &EventSerialPortReceive;

        /**
         * Description: Returns the Timestamp of the Serial Port Receive Event.
         * Visibility: 
         */
        GenApi::IInteger &EventSerialPortReceiveTimestamp;

        /**
         * Description: Returns the serial data that was received.
         * Visibility: 
         */
        GenApi::IString &EventSerialData;

        /**
         * Description: Returns the length of the received serial data that was included in the event payload.
         * Visibility: 
         */
        GenApi::IInteger &EventSerialDataLength;

        /**
         * Description: Enables/Disables the selected event.
         * Visibility: 
         */
        GenApi::IEnumerationT<EventNotificationEnums> &EventNotification;

        /**
         * Description: Controls the row of the truth table to access in the selected LUT.
         * Visibility: 
         */
        GenApi::IInteger &LogicBlockLUTRowIndex;

        /**
         * Description: Selects which LogicBlock to configure
         * Visibility: 
         */
        GenApi::IEnumerationT<LogicBlockSelectorEnums> &LogicBlockSelector;

        /**
         * Description: Selects the activation mode of the Logic Input Source signal.
         * Visibility: 
         */
        GenApi::IEnumerationT<LogicBlockLUTInputActivationEnums> &LogicBlockLUTInputActivation;

        /**
         * Description: Controls which LogicBlockLUT Input Source & Activation to access.
         * Visibility: 
         */
        GenApi::IEnumerationT<LogicBlockLUTInputSelectorEnums> &LogicBlockLUTInputSelector;

        /**
         * Description: Selects the source for the input into the Logic LUT.
         * Visibility: 
         */
        GenApi::IEnumerationT<LogicBlockLUTInputSourceEnums> &LogicBlockLUTInputSource;

        /**
         * Description: Controls the output column of the truth table for the selected LogicBlockLUTRowIndex.
         * Visibility: 
         */
        GenApi::IBoolean &LogicBlockLUTOutputValue;

        /**
         * Description: Sets the value of all the output bits in the selected LUT.
         * Visibility: 
         */
        GenApi::IInteger &LogicBlockLUTOutputValueAll;

        /**
         * Description: Selects which LogicBlock LUT to configure
         * Visibility: 
         */
        GenApi::IEnumerationT<LogicBlockLUTSelectorEnums> &LogicBlockLUTSelector;

        /**
         * Description: 
      Represents the value of the selected Gain factor
      or Offset inside the Transformation matrix in floating point precision.
    
         * Visibility: 
         */
        GenApi::IFloat &ColorTransformationValue;

        /**
         * Description: 
      Enables/disables the color transform selected with
      ColorTransformationSelector. For RGB to YUV this is read-only. Enabling/disabling RGB to YUV can only be done by changing pixel format.
    
         * Visibility: 
         */
        GenApi::IBoolean &ColorTransformationEnable;

        /**
         * Description: 
        Selects which Color Transformation module is controlled by the various Color Transformation features
      
         * Visibility: 
         */
        GenApi::IEnumerationT<ColorTransformationSelectorEnums> &ColorTransformationSelector;

        /**
         * Description: 
      Used to select from a set of RGBtoRGB transform matricies calibrated for different light sources.
      Selecting a value also sets the white balance ratios 
      (BalanceRatioRed and BalanceRatioBlue), but those can be overwritten through manual or auto white balance.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<RgbTransformLightSourceEnums> &RgbTransformLightSource;

        /**
         * Description: 
	Controls the color saturation.
	
         * Visibility: 
         */
        GenApi::IFloat &Saturation;

        /**
         * Description: 
	Enables/disables Saturation adjustment.
	
         * Visibility: 
         */
        GenApi::IBoolean &SaturationEnable;

        /**
         * Description: 
      Selects the Gain factor or Offset of the Transformation matrix to access in the selected Color Transformation module
    
         * Visibility: 
         */
        GenApi::IEnumerationT<ColorTransformationValueSelectorEnums> &ColorTransformationValueSelector;

        /**
         * Description: Returns the latched value of the timestamp counter.
         * Visibility: 
         */
        GenApi::IInteger &TimestampLatchValue;

        /**
         * Description: Resets the current value of the device timestamp counter.
         * Visibility: 
         */
        GenApi::ICommand &TimestampReset;

        /**
         * Description: User-programmable device identifier.
         * Visibility: 
         */
        GenApi::IString &DeviceUserID;

        /**
         * Description: Device temperature in degrees Celsius (C).
         * Visibility: 
         */
        GenApi::IFloat &DeviceTemperature;

        /**
         * Description: Time to wait until device reset complete (ms).
         * Visibility: 
         */
        GenApi::IInteger &MaxDeviceResetTime;

        /**
         * Description: 
      Minor version of the Transport Layer of the device.
    
         * Visibility: 
         */
        GenApi::IInteger &DeviceTLVersionMinor;

        /**
         * Description: 
      Device's serial number. This string is a unique identifier of the device.
    
         * Visibility: 
         */
        GenApi::IString &DeviceSerialNumber;

        /**
         * Description: Name of the manufacturer of the device.
         * Visibility: 
         */
        GenApi::IString &DeviceVendorName;

        /**
         * Description: Endianess of the registers of the device.
         * Visibility: 
         */
        GenApi::IEnumerationT<DeviceRegistersEndiannessEnums> &DeviceRegistersEndianness;

        /**
         * Description: Manufacturer information about the device.
         * Visibility: 
         */
        GenApi::IString &DeviceManufacturerInfo;

        /**
         * Description: 
      Indicates the speed of transmission negotiated on the specified Link.
      (Bps)
    
         * Visibility: 
         */
        GenApi::IInteger &DeviceLinkSpeed;

        /**
         * Description: Time since the last phy negotiation (enumeration).
         * Visibility: 
         */
        GenApi::IInteger &LinkUptime;

        /**
         * Description: 
      Indicates the number of event channels supported by the device.
    
         * Visibility: 
         */
        GenApi::IInteger &DeviceEventChannelCount;

        /**
         * Description: Latches the current timestamp counter into TimestampLatchValue.
         * Visibility: 
         */
        GenApi::ICommand &TimestampLatch;

        /**
         * Description: Scan type of the sensor of the device.
         * Visibility: 
         */
        GenApi::IEnumerationT<DeviceScanTypeEnums> &DeviceScanType;

        /**
         * Description: This is a command that immediately resets and reboots the device.
         * Visibility: 
         */
        GenApi::ICommand &DeviceReset;

        /**
         * Description: 
      Character set used by the strings of the device`s bootstrap registers.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<DeviceCharacterSetEnums> &DeviceCharacterSet;

        /**
         * Description: 
      Limits the maximum bandwidth of the data that will be streamed out by
      the device on the selected Link. If necessary, delays will be uniformly
      inserted between transport layer packets in order to control the peak
      bandwidth.
    
         * Visibility: 
         */
        GenApi::IInteger &DeviceLinkThroughputLimit;

        /**
         * Description: Version of the firmware on the device.
         * Visibility: 
         */
        GenApi::IString &DeviceFirmwareVersion;

        /**
         * Description: 
      Indicates the number of streaming channels supported by the device.
    
         * Visibility: 
         */
        GenApi::IInteger &DeviceStreamChannelCount;

        /**
         * Description: Transport Layer type of the device.
         * Visibility: 
         */
        GenApi::IEnumerationT<DeviceTLTypeEnums> &DeviceTLType;

        /**
         * Description: Version of the device.
         * Visibility: 
         */
        GenApi::IString &DeviceVersion;

        /**
         * Description: 
      Selects the power supply source to control or read.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<DevicePowerSupplySelectorEnums> &DevicePowerSupplySelector;

        /**
         * Description: Returns Sensor Description
         * Visibility: 
         */
        GenApi::IString &SensorDescription;

        /**
         * Description: Model of the device.
         * Visibility: 
         */
        GenApi::IString &DeviceModelName;

        /**
         * Description: 
      Major version of the Transport Layer of the device.
    
         * Visibility: 
         */
        GenApi::IInteger &DeviceTLVersionMajor;

        /**
         * Description: 
      Selects the location within the device, where the temperature will be measured.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<DeviceTemperatureSelectorEnums> &DeviceTemperatureSelector;

        /**
         * Description: Number of enumerations since uptime.
         * Visibility: 
         */
        GenApi::IInteger &EnumerationCount;

        /**
         * Description: 
      Indicates the output current of the selected power supply (A).
    
         * Visibility: 
         */
        GenApi::IFloat &PowerSupplyCurrent;

        /**
         * Description: Device identifier (serial number).
         * Visibility: 
         */
        GenApi::IString &DeviceID;

        /**
         * Description: Total time since the device was powered up in seconds.
         * Visibility: 
         */
        GenApi::IInteger &DeviceUptime;

        /**
         * Description: Current bandwidth of streamed data.
         * Visibility: 
         */
        GenApi::IInteger &DeviceLinkCurrentThroughput;

        /**
         * Description: 
      Maximum bandwidth of the data that can be streamed out of the device. 
      This can be used to estimate if the physical connection(s) can sustain 
      transfer of free-running images from the camera at its maximum speed.
    
         * Visibility: 
         */
        GenApi::IInteger &DeviceMaxThroughput;

        /**
         * Description: Returns all user tables to factory default
         * Visibility: 
         */
        GenApi::ICommand &FactoryReset;

        /**
         * Description: 
      Indicates the current voltage of the selected power supply (V).
    
         * Visibility: 
         */
        GenApi::IFloat &PowerSupplyVoltage;

        /**
         * Description: Controls the LED behaviour: Inactive (off), Active (current status), or Error Status (off unless an error occurs).
         * Visibility: 
         */
        GenApi::IEnumerationT<DeviceIndicatorModeEnums> &DeviceIndicatorMode;

        /**
         * Description: 
      Percentage of streamed data bandwidth reserved for packet resend.
    
         * Visibility: 
         */
        GenApi::IFloat &DeviceLinkBandwidthReserve;

        /**
         * Description: 
      Controls the y-offset of the ROI used by the auto algorithm that is 
      currently selected by the AutoAlgorithmSelector feature.
    
         * Visibility: 
         */
        GenApi::IInteger &AasRoiOffsetY;

        /**
         * Description: 
      Controls the x-offset of the ROI used by the auto algorithm that is
      currently selected by the AutoAlgorithmSelector feature.
    
         * Visibility: 
         */
        GenApi::IInteger &AasRoiOffsetX;

        /**
         * Description: 
      Selects whether to adjust gain or exposure first. 
      When gain priority is selected, the camera fixes the gain to 0 dB, and the exposure is adjusted according to the target grey level. If the maximum exposure is reached before the target grey level is hit, the gain starts to change to meet the target. This mode is used to have the minimum noise.
	  When exposure priority is selected, the camera sets the exposure to a small value (default is 5 ms). The gain is adjusted according to the target grey level. If maximum gain is reached before the target grey level is hit, the exposure starts to change to meet the target. This mode is used to capture fast motion. 
    
         * Visibility: 
         */
        GenApi::IEnumerationT<AutoExposureControlPriorityEnums> &AutoExposureControlPriority;

        /**
         * Description: 
      Controls the minimum value Auto White Balance can set for the 
      Red/Blue BalanceRatio.
    
         * Visibility: 
         */
        GenApi::IFloat &BalanceWhiteAutoLowerLimit;

        /**
         * Description: 
      Controls how quickly 'BalanceWhiteAuto' adjusts the values for Red and
      Blue BalanceRatio in response to changing conditions.  Higher damping
      means the changes are more gradual.
    
         * Visibility: 
         */
        GenApi::IFloat &BalanceWhiteAutoDamping;

        /**
         * Description: 
      Controls the width of the ROI used by the auto algorithm that is 
      currently selected by the AutoAlgorithmSelector feature.
    
         * Visibility: 
         */
        GenApi::IInteger &AasRoiHeight;

        /**
         * Description: 
      The highest value in percentage that the target mean may reach.
    
         * Visibility: 
         */
        GenApi::IFloat &AutoExposureGreyValueUpperLimit;

        /**
         * Description: 
      This is the user-specified target grey level (image mean) to apply to the current image. Note that the target grey level is in the linear domain before gamma correction is applied.
    
         * Visibility: 
         */
        GenApi::IFloat &AutoExposureTargetGreyValue;

        /**
         * Description: 
      The smallest gain that auto exposure can set. 
    
         * Visibility: 
         */
        GenApi::IFloat &AutoExposureGainLowerLimit;

        /**
         * Description: 
      The lowest value in percentage that the target mean may reach.
    
         * Visibility: 
         */
        GenApi::IFloat &AutoExposureGreyValueLowerLimit;

        /**
         * Description: 
      Selects a metering mode: average, spot, or partial metering.
      a. Average: Measures the light from the entire
      scene uniformly to determine the final exposure value. Every portion
      of the exposed area has the same contribution.
      b. Spot: Measures a small area (about 3%) in the
      center of the scene while the rest of the scene is ignored. This mode
      is used when the scene has a high contrast and the object of
      interest is relatively small.
      c. Partial: Measures the light from a larger area (about 11%) in the center of the scene. This mode is used when very dark or bright regions appear at the edge of the frame.
      Note: Metering mode is available only when Lighting Mode Selector is Normal. 
    
         * Visibility: 
         */
        GenApi::IEnumerationT<AutoExposureMeteringModeEnums> &AutoExposureMeteringMode;

        /**
         * Description: 
      The largest exposure time that auto exposure can set. 
    
         * Visibility: 
         */
        GenApi::IFloat &AutoExposureExposureTimeUpperLimit;

        /**
         * Description: 
      The largest gain that auto exposure can set. 
    
         * Visibility: 
         */
        GenApi::IFloat &AutoExposureGainUpperLimit;

        /**
         * Description: 
      It controls how fast the exposure and gain get settled.
      If the value is too small, it may cause the system to be unstable.
	  Range is from 0.0 to 1.0. Default = 0.2.
    
         * Visibility: 
         */
        GenApi::IFloat &AutoExposureControlLoopDamping;

        /**
         * Description: 
      The EV compensation value used in the exposure compensation. This allows you to adjust the resultant image intensity with one control.
      A positive value makes the image brighter.
      A negative value makes the image darker.
      Range from -3 to 3 with a step of 1/3. Default = 0.
    
         * Visibility: 
         */
        GenApi::IFloat &AutoExposureEVCompensation;

        /**
         * Description: 
      The smallest exposure time that auto exposure can set. 
    
         * Visibility: 
         */
        GenApi::IFloat &AutoExposureExposureTimeLowerLimit;

        /**
         * Description: Selects the profile used by BalanceWhiteAuto.
         * Visibility: 
         */
        GenApi::IEnumerationT<BalanceWhiteAutoProfileEnums> &BalanceWhiteAutoProfile;

        /**
         * Description: 
      Selects which Auto Algorithm is controlled by the RoiEnable, OffsetX, 
      OffsetY, Width, Height features.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<AutoAlgorithmSelectorEnums> &AutoAlgorithmSelector;

        /**
         * Description: 
      This indicates whether the target image grey level is automatically set by the camera or manually set by the user. Note that the target grey level is in the linear domain before gamma correction is applied.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<AutoExposureTargetGreyValueAutoEnums> &AutoExposureTargetGreyValueAuto;

        /**
         * Description: 
      Controls whether a user-specified ROI is used for auto algorithm that is
      currently selected by the AutoAlgorithmSelector feature.
    
         * Visibility: 
         */
        GenApi::IBoolean &AasRoiEnable;

        /**
         * Description: 
      Selects a lighting mode: Backlight, Frontlight or Normal (default).
      a. Backlight compensation: used when a strong light is coming from the back of the object.
      b. Frontlight compensation: used when a strong light is shining in the front of the object while the background is dark. 
      c. Normal lighting: used when the object is not under backlight or frontlight conditions. When normal lighting is selected, metering modes are available.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<AutoExposureLightingModeEnums> &AutoExposureLightingMode;

        /**
         * Description: 
      Controls the width of the ROI used by the auto algorithm that is 
      currently selected by the AutoAlgorithmSelector feature.
    
         * Visibility: 
         */
        GenApi::IInteger &AasRoiWidth;

        /**
         * Description: 
      Controls the maximum value Auto White Balance can set the Red/Blue 
      BalanceRatio.
    
         * Visibility: 
         */
        GenApi::IFloat &BalanceWhiteAutoUpperLimit;

        /**
         * Description: Counts the number of error on the link.
         * Visibility: 
         */
        GenApi::IInteger &LinkErrorCount;

        /**
         * Description: Controls whether the DHCP IP configuration scheme is activated on the given logical link.
         * Visibility: 
         */
        GenApi::IBoolean &GevCurrentIPConfigurationDHCP;

        /**
         * Description: Selects which logical link to control.
         * Visibility: 
         */
        GenApi::IInteger &GevInterfaceSelector;

        /**
         * Description: Controls the delay (in GEV timestamp counter unit) to insert between each packet for this stream channel. This can be used as a crude flow-control mechanism if the application or the network infrastructure cannot keep up with the packets coming from the device.
         * Visibility: 
         */
        GenApi::IInteger &GevSCPD;

        /**
         * Description: Indicates the number of timestamp ticks in 1 second (frequency in Hz).
         * Visibility: 
         */
        GenApi::IInteger &GevTimestampTickFrequency;

        /**
         * Description: Specifies the stream packet size (in bytes) to send on this channel.
         * Visibility: 
         */
        GenApi::IInteger &GevSCPSPacketSize;

        /**
         * Description: Reports the default gateway IP address to be used on the given logical link.
         * Visibility: 
         */
        GenApi::IInteger &GevCurrentDefaultGateway;

        /**
         * Description: Enables the camera to continue to stream, for this stream channel, if its control channel is closed or regardless of the reception of any ICMP messages (such as destination unreachable messages).
         * Visibility: 
         */
        GenApi::IBoolean &GevSCCFGUnconditionalStreaming;

        /**
         * Description: Indicates the transmission timeout of the message channel.
         * Visibility: 
         */
        GenApi::IInteger &GevMCTT;

        /**
         * Description: The state of this feature is copied into the "do not fragment" bit of the IP header of each stream packet.
         * Visibility: 
         */
        GenApi::IBoolean &GevSCPSDoNotFragment;

        /**
         * Description: Reports the subnet mask of the given logical link.
         * Visibility: 
         */
        GenApi::IInteger &GevCurrentSubnetMask;

        /**
         * Description: Selects the stream channel to control.
         * Visibility: 
         */
        GenApi::IInteger &GevStreamChannelSelector;

        /**
         * Description: Reports the IP address for the given logical link.
         * Visibility: 
         */
        GenApi::IInteger &GevCurrentIPAddress;

        /**
         * Description: Indicates the source port of the message channel.
         * Visibility: 
         */
        GenApi::IInteger &GevMCSP;

        /**
         * Description: Indicates the longest GVCP command execution time before the device returns a PENDING_ACK in milliseconds.
         * Visibility: 
         */
        GenApi::IInteger &GevGVCPPendingTimeout;

        /**
         * Description: Provides the status of the IEEE 1588 clock.
         * Visibility: 
         */
        GenApi::IEnumerationT<GevIEEE1588StatusEnums> &GevIEEE1588Status;

        /**
         * Description: The first choice of URL for the XML device description file.
         * Visibility: 
         */
        GenApi::IString &GevFirstURL;

        /**
         * Description: MAC address of the logical link.
         * Visibility: 
         */
        GenApi::IInteger &GevMACAddress;

        /**
         * Description: Controls the Persistent subnet mask associated with the Persistent IP address on this logical link.
         * Visibility: 
         */
        GenApi::IInteger &GevPersistentSubnetMask;

        /**
         * Description: The port to which the device must send messages
         * Visibility: 
         */
        GenApi::IInteger &GevMCPHostPort;

        /**
         * Description: Controls the port of the selected channel to which a GVSP transmitter must send data stream or the port from which a GVSP receiver may receive data stream.
         * Visibility: 
         */
        GenApi::IInteger &GevSCPHostPort;

        /**
         * Description: Enables the generation of PENDING_ACK.
         * Visibility: 
         */
        GenApi::IBoolean &GevGVCPPendingAck;

        /**
         * Description: Index of the logical link to use.
         * Visibility: 
         */
        GenApi::IInteger &GevSCPInterfaceIndex;

        /**
         * Description: Returns if the selected GEV option is supported.
         * Visibility: 
         */
        GenApi::IBoolean &GevSupportedOption;

        /**
         * Description: Provides the mode of the IEEE 1588 clock.
         * Visibility: 
         */
        GenApi::IEnumerationT<GevIEEE1588ModeEnums> &GevIEEE1588Mode;

        /**
         * Description: Controls whether the Link Local Address IP configuration scheme is activated on the given logical link.
         * Visibility: 
         */
        GenApi::IBoolean &GevCurrentIPConfigurationLLA;

        /**
         * Description: Indicates the source port of the stream channel.
         * Visibility: 
         */
        GenApi::IInteger &GevSCSP;

        /**
         * Description: Enables the IEEE 1588 Precision Time Protocol to control the timestamp register.
         * Visibility: 
         */
        GenApi::IBoolean &GevIEEE1588;

        /**
         * Description: Enables cameras to use the extended chunk data payload type for this stream channel.
         * Visibility: 
         */
        GenApi::IBoolean &GevSCCFGExtendedChunkData;

        /**
         * Description: Controls the Persistent IP address for this logical link.
         * Visibility: 
         */
        GenApi::IInteger &GevPersistentIPAddress;

        /**
         * Description: Controls whether the PersistentIP configuration scheme is activated on the given logical link.
         * Visibility: 
         */
        GenApi::IBoolean &GevCurrentIPConfigurationPersistentIP;

        /**
         * Description: Indicates the expected accuracy of the device clock when it is the grandmaster, or in the event it becomes the grandmaster.
         * Visibility: 
         */
        GenApi::IEnumerationT<GevIEEE1588ClockAccuracyEnums> &GevIEEE1588ClockAccuracy;

        /**
         * Description: Indicates the current heartbeat timeout in milliseconds.
         * Visibility: 
         */
        GenApi::IInteger &GevHeartbeatTimeout;

        /**
         * Description: Controls the persistent default gateway for this logical link.
         * Visibility: 
         */
        GenApi::IInteger &GevPersistentDefaultGateway;

        /**
         * Description: Controls the device access privilege of an application.
         * Visibility: 
         */
        GenApi::IEnumerationT<GevCCPEnums> &GevCCP;

        /**
         * Description: Controls the destination IP address of the message channel
         * Visibility: 
         */
        GenApi::IInteger &GevMCDA;

        /**
         * Description: Controls the destination IP address of the selected stream channel to which a GVSP transmitter must send data stream or the destination IP address from which a GVSP receiver may receive data stream.
         * Visibility: 
         */
        GenApi::IInteger &GevSCDA;

        /**
         * Description: Transmit or Receive of the channel
         * Visibility: 
         */
        GenApi::IInteger &GevSCPDirection;

        /**
         * Description: Sends a test packet.
         * Visibility: 
         */
        GenApi::IBoolean &GevSCPSFireTestPacket;

        /**
         * Description: The second choice of URL to the XML device description file.
         * Visibility: 
         */
        GenApi::IString &GevSecondURL;

        /**
         * Description: Selects the GEV option to interrogate for existing support.
         * Visibility: 
         */
        GenApi::IEnumerationT<GevSupportedOptionSelectorEnums> &GevSupportedOptionSelector;

        /**
         * Description: Disables the GVCP heartbeat.
         * Visibility: 
         */
        GenApi::IBoolean &GevGVCPHeartbeatDisable;

        /**
         * Description: Indicates the number of retries of the message channel.
         * Visibility: 
         */
        GenApi::IInteger &GevMCRC;

        /**
         * Description: Endianess of multi-byte pixel data for this stream.
         * Visibility: 
         */
        GenApi::IBoolean &GevSCPSBigEndian;

        /**
         * Description: Indicates the number of physical network interfaces supported by this device.
         * Visibility: 
         */
        GenApi::IInteger &GevNumberOfInterfaces;

        /**
         * Description: 
         * Visibility: 
         */
        GenApi::IInteger &TLParamsLocked;

        /**
         * Description: Provides the number of bytes transferred for each image or chunk on the stream channel.
         * Visibility: 
         */
        GenApi::IInteger &PayloadSize;

        /**
         * Description: Counts the number of resend requests received from the host.
         * Visibility: 
         */
        GenApi::IInteger &PacketResendRequestCount;

        /**
         * Description: 
      Enables/disables the sharpening feature. Sharpening is disabled by default.
    
         * Visibility: 
         */
        GenApi::IBoolean &SharpeningEnable;

        /**
         * Description: 
      Selects which black level to control.  Only All can be set by the user. Analog and Digital are read-only.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<BlackLevelSelectorEnums> &BlackLevelSelector;

        /**
         * Description: Enables/disables gamma correction.
         * Visibility: 
         */
        GenApi::IBoolean &GammaEnable;

        /**
         * Description: 
      Enables/disables the auto sharpening feature. When enabled, the camera automatically determines the sharpening threshold based on the noise level of the camera.
    
         * Visibility: 
         */
        GenApi::IBoolean &SharpeningAuto;

        /**
         * Description: 
      Enable the black level auto clamping feature which performing dark current compensation.
    
         * Visibility: 
         */
        GenApi::IBoolean &BlackLevelClampingEnable;

        /**
         * Description: 
      Controls the balance ratio of the selected color relative to green. 
      Used for white balancing.
    
         * Visibility: 
         */
        GenApi::IFloat &BalanceRatio;

        /**
         * Description: 
      White Balance compensates for color shifts caused by different lighting conditions. It can be automatically or manually controlled. For manual control, set to Off. For automatic control, set to Once or Continuous.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<BalanceWhiteAutoEnums> &BalanceWhiteAuto;

        /**
         * Description: 
      Controls the minimum intensity gradient change to invoke sharpening.
      When "Sharpening Auto" is enabled, this is determined automatically by the device.
	  The threshold is specified as a fraction of the total intensity range, and ranges from 0 to 0.25. A threshold higher than 25% produces little to no difference than 25%. High thresholds sharpen only areas with significant intensity changes. Low thresholds sharpen more areas.
    
         * Visibility: 
         */
        GenApi::IFloat &SharpeningThreshold;

        /**
         * Description: 
      Sets the automatic gain mode. Set to Off for manual control. Set to Once for a single automatic adjustment then return to Off. Set to Continuous for constant adjustment. In automatic modes, the camera adjusts the gain to maximize the dynamic range.
         * Visibility: 
         */
        GenApi::IEnumerationT<GainAutoEnums> &GainAuto;

        /**
         * Description: 
      Controls the amount to sharpen a signal.
      The sharpened amount is proportional to the difference between a pixel and its neighbors.
      A negative value smooths out the difference, while a positive value amplifies the difference.
      You can boost by a maximum of 8x, but smoothing is limited to 1x  (in float).
      Default value: 2.0
    
         * Visibility: 
         */
        GenApi::IFloat &Sharpening;

        /**
         * Description: 
      Controls the amplification of the video signal in dB.
    
         * Visibility: 
         */
        GenApi::IFloat &Gain;

        /**
         * Description: 
      Selects a balance ratio to configure once a balance ratio control has 
      been selected.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<BalanceRatioSelectorEnums> &BalanceRatioSelector;

        /**
         * Description: 
	Selects which gain to control. The All selection is a total amplification across all channels (or taps).
	
         * Visibility: 
         */
        GenApi::IEnumerationT<GainSelectorEnums> &GainSelector;

        /**
         * Description: 
      Controls the offset of the video signal in percent.
    
         * Visibility: 
         */
        GenApi::IFloat &BlackLevel;

        /**
         * Description: 
      Controls the offset of the video signal in camera specific units.
    
         * Visibility: 
         */
        GenApi::IInteger &BlackLevelRaw;

        /**
         * Description: 
	  Controls the gamma correction of pixel intensity.
	
         * Visibility: 
         */
        GenApi::IFloat &Gamma;

        /**
         * Description: 
      Controls the offset of the element to access in the defective pixel location table.
    
         * Visibility: 
         */
        GenApi::IInteger &DefectTableIndex;

        /**
         * Description: 
    	Restores the Defective Pixel Table to its factory default state, which was calibrated during manufacturing.
        This permanently overwrites any changes made to the defect table.
   	
         * Visibility: 
         */
        GenApi::ICommand &DefectTableFactoryRestore;

        /**
         * Description: 
      Returns the Y coordinate of the defective pixel at DefectTableIndex within the defective pixel table.
      Changes made do not take effect in captured images until the command DefectTableApply is written.
    
         * Visibility: 
         */
        GenApi::IInteger &DefectTableCoordinateY;

        /**
         * Description: 
    	Saves the current defective pixel table non-volatile memory, 
    	so that it is preserved when the camera boots up.
    	This overwrites the existing defective pixel table.  
    	The new table is loaded whenever the camera 
    	powers up.
    
         * Visibility: 
         */
        GenApi::ICommand &DefectTableSave;

        /**
         * Description: 
    	Controls the method used for replacing defective pixels.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<DefectCorrectionModeEnums> &DefectCorrectionMode;

        /**
         * Description: 
      Returns the X coordinate of the defective pixel at DefectTableIndex within the defective pixel table.
      Changes made do not take effect in captured images until the command DefectTableApply is written.
    
         * Visibility: 
         */
        GenApi::IInteger &DefectTableCoordinateX;

        /**
         * Description: 
      The number of defective pixel locations in the current table.
    
         * Visibility: 
         */
        GenApi::IInteger &DefectTablePixelCount;

        /**
         * Description: Enables/Disables table-based defective pixel correction.
         * Visibility: 
         */
        GenApi::IBoolean &DefectCorrectStaticEnable;

        /**
         * Description: 
    	Applies the current defect table, so that any changes made 
    	affect images captured by the camera.
    	This writes the table to volatile memory, so changes to the 
    	table are lost if the camera loses power. To save the 
    	table to non-volatile memory, use DefectTableSave.
    
         * Visibility: 
         */
        GenApi::ICommand &DefectTableApply;

        /**
         * Description: 
	Whether or not the selected feature is saved to user sets.
         * Visibility: 
         */
        GenApi::IBoolean &UserSetFeatureEnable;

        /**
         * Description: 
      Saves the User Set specified by UserSetSelector to the non-volatile memory of the device.
    
         * Visibility: 
         */
        GenApi::ICommand &UserSetSave;

        /**
         * Description: 
      Selects the feature User Set to load, save or configure.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<UserSetSelectorEnums> &UserSetSelector;

        /**
         * Description: 
      Loads the User Set specified by UserSetSelector to the device and makes it active.
    
         * Visibility: 
         */
        GenApi::ICommand &UserSetLoad;

        /**
         * Description: 
      Selects the feature User Set to load and make active by default when the device is restarted.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<UserSetDefaultEnums> &UserSetDefault;

        /**
         * Description: This feature controls the baud rate used by the selected serial port.
         * Visibility: 
         */
        GenApi::IEnumerationT<SerialPortBaudRateEnums> &SerialPortBaudRate;

        /**
         * Description: This feature controls the number of data bits used by the selected serial port.  Possible values that can be used are between 5 and 9.
         * Visibility: 
         */
        GenApi::IInteger &SerialPortDataBits;

        /**
         * Description: This feature controls the parity used by the selected serial port.
         * Visibility: 
         */
        GenApi::IEnumerationT<SerialPortParityEnums> &SerialPortParity;

        /**
         * Description: >Returns the maximum number of characters in the serial port transmit queue.
         * Visibility: 
         */
        GenApi::IInteger &SerialTransmitQueueMaxCharacterCount;

        /**
         * Description: Returns the number of characters currently in the serial port receive queue.
         * Visibility: 
         */
        GenApi::IInteger &SerialReceiveQueueCurrentCharacterCount;

        /**
         * Description: Selects which serial port of the device to control.
         * Visibility: 
         */
        GenApi::IEnumerationT<SerialPortSelectorEnums> &SerialPortSelector;

        /**
         * Description: This feature controls the number of stop bits used by the selected serial port.
         * Visibility: 
         */
        GenApi::IEnumerationT<SerialPortStopBitsEnums> &SerialPortStopBits;

        /**
         * Description: This is a command that clears the device serial port receive queue.
         * Visibility: 
         */
        GenApi::ICommand &SerialReceiveQueueClear;

        /**
         * Description: Returns the number of framing errors that have occurred on the serial port.
         * Visibility: 
         */
        GenApi::IInteger &SerialReceiveFramingErrorCount;

        /**
         * Description: Returns the number of characters currently in the serial port transmit queue.
         * Visibility: 
         */
        GenApi::IInteger &SerialTransmitQueueCurrentCharacterCount;

        /**
         * Description: Returns the number of parity errors that have occurred on the serial port.
         * Visibility: 
         */
        GenApi::IInteger &SerialReceiveParityErrorCount;

        /**
         * Description: Specifies the physical input Line on which to receive serial data.
         * Visibility: 
         */
        GenApi::IEnumerationT<SerialPortSourceEnums> &SerialPortSource;

        /**
         * Description: >Returns the maximum number of characters in the serial port receive queue.
         * Visibility: 
         */
        GenApi::IInteger &SerialReceiveQueueMaxCharacterCount;

        /**
         * Description: Sets the first sequencer set to be used.
         * Visibility: 
         */
        GenApi::IInteger &SequencerSetStart;

        /**
         * Description: Controls whether or not a sequencer is active.
         * Visibility: 
         */
        GenApi::IEnumerationT<SequencerModeEnums> &SequencerMode;

        /**
         * Description: 
      Display whether the current sequencer configuration is valid to run.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<SequencerConfigurationValidEnums> &SequencerConfigurationValid;

        /**
         * Description: 
      Displays whether the currently selected sequencer set's register contents 
      are valid to use.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<SequencerSetValidEnums> &SequencerSetValid;

        /**
         * Description: 
      Selects the sequencer set to which subsequent settings apply.
    
         * Visibility: 
         */
        GenApi::IInteger &SequencerSetSelector;

        /**
         * Description: 
      Specifies the activation mode of the sequencer trigger.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<SequencerTriggerActivationEnums> &SequencerTriggerActivation;

        /**
         * Description: 
      Controls whether or not a sequencer is in configuration mode.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<SequencerConfigurationModeEnums> &SequencerConfigurationMode;

        /**
         * Description: 
      Saves the current device configuration to the currently selected 
      sequencer set.
    
         * Visibility: 
         */
        GenApi::ICommand &SequencerSetSave;

        /**
         * Description: 
      Specifies the internal signal or physical input line to use as the 
      sequencer trigger source.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<SequencerTriggerSourceEnums> &SequencerTriggerSource;

        /**
         * Description: Displays the currently active sequencer set.
         * Visibility: 
         */
        GenApi::IInteger &SequencerSetActive;

        /**
         * Description: Specifies the next sequencer set.
         * Visibility: 
         */
        GenApi::IInteger &SequencerSetNext;

        /**
         * Description: 
      Loads currently selected sequencer to the current device configuration.
    
         * Visibility: 
         */
        GenApi::ICommand &SequencerSetLoad;

        /**
         * Description: 
      Selects branching path to be used for subsequent settings.
    
         * Visibility: 
         */
        GenApi::IInteger &SequencerPathSelector;

        /**
         * Description: 
      Enables the selected feature and makes it active in all sequencer sets.
    
         * Visibility: 
         */
        GenApi::IBoolean &SequencerFeatureEnable;

        /**
         * Description: Specifies the number of data blocks (images) that the device should stream before stopping. This feature is only active if the Transfer Operation Mode is set to Multi Block.
         * Visibility: 
         */
        GenApi::IInteger &TransferBlockCount;

        /**
         * Description: Starts the streaming of data blocks (images) out of the device. This feature is available when the Transfer Control Mode is set to User Controlled.
         * Visibility: 
         */
        GenApi::ICommand &TransferStart;

        /**
         * Description: Returns the maximum number of data blocks (images) in the transfer queue
         * Visibility: 
         */
        GenApi::IInteger &TransferQueueMaxBlockCount;

        /**
         * Description: Returns number of data blocks (images) currently in the transfer queue.
         * Visibility: 
         */
        GenApi::IInteger &TransferQueueCurrentBlockCount;

        /**
         * Description: Specifies the operation mode of the transfer queue.
         * Visibility: 
         */
        GenApi::IEnumerationT<TransferQueueModeEnums> &TransferQueueMode;

        /**
         * Description: Selects the operation mode of the transfer. Continuous is similar to Basic/Automatic but you can start/stop the transfer while acquisition runs independently. Multi Block transmits a specified number of blocks and then stops.
         * Visibility: 
         */
        GenApi::IEnumerationT<TransferOperationModeEnums> &TransferOperationMode;

        /**
         * Description: Stops the streaming of data block (images). The current block transmission is completed. This feature is available when the Transfer Control Mode is set to User Controlled.
         * Visibility: 
         */
        GenApi::ICommand &TransferStop;

        /**
         * Description: Returns number of images that have been lost before being transmitted because the transmit queue hasn't been cleared fast enough.
    
         * Visibility: 
         */
        GenApi::IInteger &TransferQueueOverflowCount;

        /**
         * Description: Selects the control method for the transfers. Basic and Automatic start transmitting data as soon as there is enough data to fill a link layer packet. User Controlled allows you to directly control the transfer of blocks.
         * Visibility: 
         */
        GenApi::IEnumerationT<TransferControlModeEnums> &TransferControlMode;

        /**
         * Description: Returns the black level used to capture the image.
         * Visibility: 
         */
        GenApi::IFloat &ChunkBlackLevel;

        /**
         * Description: Returns the image frame ID.
         * Visibility: 
         */
        GenApi::IInteger &ChunkFrameID;

        /**
         * Description: Returns the serial data that was received.
         * Visibility: 
         */
        GenApi::IString &ChunkSerialData;

        /**
         * Description: Returns the exposure time used to capture the image.
         * Visibility: 
         */
        GenApi::IFloat &ChunkExposureTime;

        /**
         * Description: Returns the status of the chunk serial receive overflow.
         * Visibility: 
         */
        GenApi::IBoolean &ChunkSerialReceiveOverflow;

        /**
         * Description: Returns the Timestamp of the image.
         * Visibility: 
         */
        GenApi::IInteger &ChunkTimestamp;

        /**
         * Description: Activates the inclusion of Chunk data in the payload of the image.
         * Visibility: 
         */
        GenApi::IBoolean &ChunkModeActive;

        /**
         * Description: Returns the status of all the I/O lines at the end of exposure event.
         * Visibility: 
         */
        GenApi::IInteger &ChunkExposureEndLineStatusAll;

        /**
         * Description: Selects which gain to retrieve
         * Visibility: 
         */
        GenApi::IEnumerationT<ChunkGainSelectorEnums> &ChunkGainSelector;

        /**
         * Description: Selects which chunk data to enable or disable.
         * Visibility: 
         */
        GenApi::IEnumerationT<ChunkSelectorEnums> &ChunkSelector;

        /**
         * Description: Selects which black level to retrieve
         * Visibility: 
         */
        GenApi::IEnumerationT<ChunkBlackLevelSelectorEnums> &ChunkBlackLevelSelector;

        /**
         * Description: Returns the width of the image included in the payload.
         * Visibility: 
         */
        GenApi::IInteger &ChunkWidth;

        /**
         * Description: Returns the image payload.
         * Visibility: 
         */
        GenApi::IInteger &ChunkImage;

        /**
         * Description: Returns the height of the image included in the payload.
         * Visibility: 
         */
        GenApi::IInteger &ChunkHeight;

        /**
         * Description: Format of the pixel provided by the camera
         * Visibility: 
         */
        GenApi::IEnumerationT<ChunkPixelFormatEnums> &ChunkPixelFormat;

        /**
         * Description: Returns the gain used to capture the image.
         * Visibility: 
         */
        GenApi::IFloat &ChunkGain;

        /**
         * Description: Returns the index of the active set of the running sequencer included in the payload.
         * Visibility: 
         */
        GenApi::IInteger &ChunkSequencerSetActive;

        /**
         * Description: Returns the CRC of the image payload.
         * Visibility: 
         */
        GenApi::IInteger &ChunkCRC;

        /**
         * Description: Returns the Offset X of the image included in the payload.
         * Visibility: 
         */
        GenApi::IInteger &ChunkOffsetX;

        /**
         * Description: Returns the Offset Y of the image included in the payload.
         * Visibility: 
         */
        GenApi::IInteger &ChunkOffsetY;

        /**
         * Description: Enables the inclusion of the selected Chunk data in the payload of the image.
         * Visibility: 
         */
        GenApi::IBoolean &ChunkEnable;

        /**
         * Description: Returns the length of the received serial data that was included in the payload.
         * Visibility: 
         */
        GenApi::IInteger &ChunkSerialDataLength;

        /**
         * Description: Controls the Offset of the mapping between the device file storage and the FileAccessBuffer.
         * Visibility: 
         */
        GenApi::IInteger &FileAccessOffset;

        /**
         * Description: Controls the Length of the mapping between the device file storage and the FileAccessBuffer.
         * Visibility: 
         */
        GenApi::IInteger &FileAccessLength;

        /**
         * Description: Represents the file operation execution status.
         * Visibility: 
         */
        GenApi::IEnumerationT<FileOperationStatusEnums> &FileOperationStatus;

        /**
         * Description: 
      This is a command that executes the selected file operation on the selected file.
    
         * Visibility: 
         */
        GenApi::ICommand &FileOperationExecute;

        /**
         * Description: 
      The mode of the file when it is opened. The file can be opened for reading, writting or both. This must be set before opening the file.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<FileOpenModeEnums> &FileOpenMode;

        /**
         * Description: Represents the file operation result. For Read or Write operations, the number of successfully read/written bytes is returned.
         * Visibility: 
         */
        GenApi::IInteger &FileOperationResult;

        /**
         * Description: 
      Sets operation to execute on the selected file when the execute command is given.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<FileOperationSelectorEnums> &FileOperationSelector;

        /**
         * Description: 
      Selects which file is being operated on. This must be set before performing any file operations.
	
         * Visibility: 
         */
        GenApi::IEnumerationT<FileSelectorEnums> &FileSelector;

        /**
         * Description: Represents the size of the selected file in bytes.
         * Visibility: 
         */
        GenApi::IInteger &FileSize;

        /**
         * Description: 
      Selects which binning engine is controlled by the BinningHorizontal and 
      BinningVertical features.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<BinningSelectorEnums> &BinningSelector;

        /**
         * Description: 
	Minimum value that can be returned during the digitization process. This corresponds to the darkest value of the camera. For color cameras, this returns the smallest value that each color component can take.
	
         * Visibility: 
         */
        GenApi::IInteger &PixelDynamicRangeMin;

        /**
         * Description: 
	Maximum value that can be returned during the digitization process. This corresponds to the brightest value of the camera. For color cameras, this returns the biggest value that each color component can take.
	
         * Visibility: 
         */
        GenApi::IInteger &PixelDynamicRangeMax;

        /**
         * Description: 
      Vertical offset from the origin to the ROI (in pixels).
    
         * Visibility: 
         */
        GenApi::IInteger &OffsetY;

        /**
         * Description: 
      Number of horizontal photo-sensitive cells to combine together. This 
      reduces the horizontal resolution (width) of the image.
      A value of 1 indicates that no horizontal binning is performed by the
      camera. This value must be 1 for decimation to be active.
    
         * Visibility: 
         */
        GenApi::IInteger &BinningHorizontal;

        /**
         * Description: 
      Width of the image provided by the device (in pixels).
    
         * Visibility: 
         */
        GenApi::IInteger &Width;

        /**
         * Description: 
      Selects which test pattern generator is controlled by the TestPattern feature.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<TestPatternGeneratorSelectorEnums> &TestPatternGeneratorSelector;

        /**
         * Description: Reports the ratio between the uncompressed image size and compressed image size.
         * Visibility: 
         */
        GenApi::IFloat &CompressionRatio;

        /**
         * Description: 
	Horizontally flips the image sent by the device. The region of interest is applied after flipping. For color cameras the bayer pixel format is affected. For example, BayerRG16 changes to BayerGR16.
	
         * Visibility: 
         */
        GenApi::IBoolean &ReverseX;

        /**
         * Description: 
	Vertically flips the image sent by the device. The region of interest is applied after flipping. For color cameras the bayer pixel format is affected. For example, BayerRG16 changes to BayerGB16.
	
         * Visibility: 
         */
        GenApi::IBoolean &ReverseY;

        /**
         * Description: 
      Selects the type of test pattern that is generated by the device as image source.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<TestPatternEnums> &TestPattern;

        /**
         * Description: 
	Type of color filter that is applied to the image. Only applies to Bayer pixel formats. All others have no color filter.
	
         * Visibility: 
         */
        GenApi::IEnumerationT<PixelColorFilterEnums> &PixelColorFilter;

        /**
         * Description: 
      Maximum width of the image (in pixels). The dimension is calculated after horizontal binning.
      WidthMax does not take into account the current Region of interest (Width or OffsetX).
    
         * Visibility: 
         */
        GenApi::IInteger &WidthMax;

        /**
         * Description: 
      Selects which ADC bit depth to use. A higher ADC bit depth results in better image quality but slower maximum frame rate.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<AdcBitDepthEnums> &AdcBitDepth;

        /**
         * Description: 
      Number of vertical photo-sensitive cells to combine together. This 
      reduces the vertical resolution (height) of the image. 
      A value of 1 indicates that no vertical binning is performed by the
      camera. This value must be 1 for decimation to be active.
    
         * Visibility: 
         */
        GenApi::IInteger &BinningVertical;

        /**
         * Description: 
      The mode used to reduce the horizontal resolution when DecimationHorizontal is used.
      The current implementation only supports a single decimation mode: Discard.  Average should be achieved via Binning.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<DecimationHorizontalModeEnums> &DecimationHorizontalMode;

        /**
         * Description: 
         * Visibility: 
         */
        GenApi::IEnumerationT<BinningVerticalModeEnums> &BinningVerticalMode;

        /**
         * Description: 
      Horizontal offset from the origin to the ROI (in pixels).
    
         * Visibility: 
         */
        GenApi::IInteger &OffsetX;

        /**
         * Description: Maximum height of the image (in pixels). This dimension is calculated after vertical binning.  
    HeightMax does not take into account the current Region of interest (Height or OffsetY).
         * Visibility: 
         */
        GenApi::IInteger &HeightMax;

        /**
         * Description: 
      Horizontal decimation of the image.  This reduces the horizontal resolution (width) of the image by only retaining a single pixel
      within a window whose size is the decimation factor specified here. A value of 1 indicates that no horizontal decimation is performed by the camera. This value must be 1 for binning to be active.
    
         * Visibility: 
         */
        GenApi::IInteger &DecimationHorizontal;

        /**
         * Description: 
	Total size in bits of a pixel of the image.
	
         * Visibility: 
         */
        GenApi::IEnumerationT<PixelSizeEnums> &PixelSize;

        /**
         * Description: Effective height of the sensor in pixels.
         * Visibility: 
         */
        GenApi::IInteger &SensorHeight;

        /**
         * Description: Selects which decimation layer is controlled by the DecimationHorizontal and DecimationVertical features.
         * Visibility: 
         */
        GenApi::IEnumerationT<DecimationSelectorEnums> &DecimationSelector;

        /**
         * Description: 
      Controls whether the image processing core is used for optional pixel
      format mode (i.e. mono).
    
         * Visibility: 
         */
        GenApi::IBoolean &IspEnable;

        /**
         * Description: Controls whether lossless compression adapts to the image content.  If disabled, a fixed encoding table is used.
         * Visibility: 
         */
        GenApi::IBoolean &AdaptiveCompressionEnable;

        /**
         * Description: 
         * Visibility: 
         */
        GenApi::IEnumerationT<ImageCompressionModeEnums> &ImageCompressionMode;

        /**
         * Description: 
      Vertical decimation of the image.  This reduces the vertical resolution (height) of the image by only retaining a single pixel
      within a window whose size is the decimation factor specified here. A value of 1 indicates that no vertical decimation is performed by the camera. This value must be 1 for binning to be active.
    
         * Visibility: 
         */
        GenApi::IInteger &DecimationVertical;

        /**
         * Description: 
      Height of the image provided by the device (in pixels).
    
         * Visibility: 
         */
        GenApi::IInteger &Height;

        /**
         * Description: 
         * Visibility: 
         */
        GenApi::IEnumerationT<BinningHorizontalModeEnums> &BinningHorizontalMode;

        /**
         * Description: 
	Format of the pixel provided by the camera.
	
         * Visibility: 
         */
        GenApi::IEnumerationT<PixelFormatEnums> &PixelFormat;

        /**
         * Description: Effective width of the sensor in pixels.
         * Visibility: 
         */
        GenApi::IInteger &SensorWidth;

        /**
         * Description: 
      The mode used to reduce the vertical resolution when DecimationVertical is used.
      The current implementation only supports a single decimation mode: Discard.  Average should be achieved via Binning.
    
         * Visibility: 
         */
        GenApi::IEnumerationT<DecimationVerticalModeEnums> &DecimationVerticalMode;

        /**
         * Description: This command generates a test event and sends it to the host.
         * Visibility: 
         */
        GenApi::ICommand &TestEventGenerate;

        /**
         * Description: This command generates a test event and sends it to the host.
         * Visibility: 
         */
        GenApi::ICommand &TriggerEventTest;

        /**
         * Description: Location of the GUI XML manifest table.
         * Visibility: 
         */
        GenApi::IInteger &GuiXmlManifestAddress;

        /**
         * Description: For testing only.
         * Visibility: 
         */
        GenApi::IInteger &Test0001;

        /**
         * Description: Internally generated 3.3V rail. Enable to supply external circuits with power. This is different than standard logic outputs in that it is comparatively slow to switch but can supply a more significant amount of power. This is only available on some pins.
         * Visibility: 
         */
        GenApi::IBoolean &V3_3Enable;

        /**
         * Description: Controls if the physical Line is used to Input or Output a signal.
         * Visibility: 
         */
        GenApi::IEnumerationT<LineModeEnums> &LineMode;

        /**
         * Description: Selects which internal acquisition or I/O source signal to output on the selected line. LineMode must be Output.
         * Visibility: 
         */
        GenApi::IEnumerationT<LineSourceEnums> &LineSource;

        /**
         * Description: Selects the kind of input filter to configure: Deglitch or Debounce.
         * Visibility: 
         */
        GenApi::IEnumerationT<LineInputFilterSelectorEnums> &LineInputFilterSelector;

        /**
         * Description: Value of the selected user output, either logic high (enabled) or logic low (disabled).
         * Visibility: 
         */
        GenApi::IBoolean &UserOutputValue;

        /**
         * Description: Returns the current status of all the user output status bits in a hexadecimal representation (UserOutput 0 status corresponds to bit 0, UserOutput 1 status with bit 1, etc). This allows simultaneous reading of all user output statuses at once.
         * Visibility: 
         */
        GenApi::IInteger &UserOutputValueAll;

        /**
         * Description: Selects which bit of the User Output register is set by UserOutputValue.
         * Visibility: 
         */
        GenApi::IEnumerationT<UserOutputSelectorEnums> &UserOutputSelector;

        /**
         * Description: Returns the current status of the selected input or output Line
         * Visibility: 
         */
        GenApi::IBoolean &LineStatus;

        /**
         * Description: Displays the current electrical format of the selected physical input or output Line.
         * Visibility: 
         */
        GenApi::IEnumerationT<LineFormatEnums> &LineFormat;

        /**
         * Description: Returns the current status of all the line status bits in a hexadecimal representation (Line 0 status corresponds to bit 0, Line 1 status with bit 1, etc). This allows simultaneous reading of all line statuses at once.
         * Visibility: 
         */
        GenApi::IInteger &LineStatusAll;

        /**
         * Description: Selects the physical line (or pin) of the external device connector to configure
         * Visibility: 
         */
        GenApi::IEnumerationT<LineSelectorEnums> &LineSelector;

        /**
         * Description: Control sensor active exposure mode.
         * Visibility: 
         */
        GenApi::IEnumerationT<ExposureActiveModeEnums> &ExposureActiveMode;

        /**
         * Description: Controls the inversion of the signal of the selected input or output line.
         * Visibility: 
         */
        GenApi::IBoolean &LineInverter;

        /**
         * Description: Filter width in microseconds for the selected line and filter combination
         * Visibility: 
         */
        GenApi::IFloat &LineFilterWidth;

        /**
         * Description: Selects the activation mode of the trigger to start the Counter.
         * Visibility: 
         */
        GenApi::IEnumerationT<CounterTriggerActivationEnums> &CounterTriggerActivation;

        /**
         * Description: Current counter value
         * Visibility: 
         */
        GenApi::IInteger &CounterValue;

        /**
         * Description: Selects which counter to configure
         * Visibility: 
         */
        GenApi::IEnumerationT<CounterSelectorEnums> &CounterSelector;

        /**
         * Description: Value of the selected Counter when it was reset by a trigger.
         * Visibility: 
         */
        GenApi::IInteger &CounterValueAtReset;

        /**
         * Description: Returns the current status of the Counter.
         * Visibility: 
         */
        GenApi::IEnumerationT<CounterStatusEnums> &CounterStatus;

        /**
         * Description: Selects the source of the trigger to start the counter
         * Visibility: 
         */
        GenApi::IEnumerationT<CounterTriggerSourceEnums> &CounterTriggerSource;

        /**
         * Description: Sets the delay (or number of events) before the CounterStart event is generated.
         * Visibility: 
         */
        GenApi::IInteger &CounterDelay;

        /**
         * Description: Selects the signal that will be the source to reset the Counter.
         * Visibility: 
         */
        GenApi::IEnumerationT<CounterResetSourceEnums> &CounterResetSource;

        /**
         * Description: Selects the event that will increment the counter
         * Visibility: 
         */
        GenApi::IEnumerationT<CounterEventSourceEnums> &CounterEventSource;

        /**
         * Description: Selects the activation mode of the event to increment the Counter.
         * Visibility: 
         */
        GenApi::IEnumerationT<CounterEventActivationEnums> &CounterEventActivation;

        /**
         * Description: Sets the duration (or number of events) before the CounterEnd event is generated.
         * Visibility: 
         */
        GenApi::IInteger &CounterDuration;

        /**
         * Description: Selects the Activation mode of the Counter Reset Source signal.
         * Visibility: 
         */
        GenApi::IEnumerationT<CounterResetActivationEnums> &CounterResetActivation;

        /**
         * Description: Returns the device type.
         * Visibility: Guru
         */
        GenApi::IEnumerationT<DeviceTypeEnums> &DeviceType;

        /**
         * Description: Identifier of the product family of the device.
         * Visibility: Beginner
         */
        GenApi::IString &DeviceFamilyName;

        /**
         * Description: Major version of the Standard Features Naming Convention that was used to create the device's GenICam XML.
         * Visibility: Beginner
         */
        GenApi::IInteger &DeviceSFNCVersionMajor;

        /**
         * Description: Minor version of the Standard Features Naming Convention that was used to create the device's GenICam XML.
         * Visibility: Beginner
         */
        GenApi::IInteger &DeviceSFNCVersionMinor;

        /**
         * Description: Sub minor version of Standard Features Naming Convention that was used to create the device's GenICam XML.
         * Visibility: Beginner
         */
        GenApi::IInteger &DeviceSFNCVersionSubMinor;

        /**
         * Description: Selects the manifest entry to reference.
         * Visibility: Guru
         */
        GenApi::IInteger &DeviceManifestEntrySelector;

        /**
         * Description: Indicates the major version number of the GenICam XML file of the selected manifest entry.
         * Visibility: Guru
         */
        GenApi::IInteger &DeviceManifestXMLMajorVersion;

        /**
         * Description: Indicates the minor version number of the GenICam XML file of the selected manifest entry.
         * Visibility: Guru
         */
        GenApi::IInteger &DeviceManifestXMLMinorVersion;

        /**
         * Description: Indicates the subminor version number of the GenICam XML file of the selected manifest entry.
         * Visibility: Guru
         */
        GenApi::IInteger &DeviceManifestXMLSubMinorVersion;

        /**
         * Description: Indicates the major version number of the schema file of the selected manifest entry.
         * Visibility: Guru
         */
        GenApi::IInteger &DeviceManifestSchemaMajorVersion;

        /**
         * Description: Indicates the minor version number of the schema file of the selected manifest entry.
         * Visibility: Guru
         */
        GenApi::IInteger &DeviceManifestSchemaMinorVersion;

        /**
         * Description: Indicates the first URL to the GenICam XML device description file of the selected manifest entry.
         * Visibility: Guru
         */
        GenApi::IString &DeviceManifestPrimaryURL;

        /**
         * Description: Indicates the second URL to the GenICam XML device description file of the selected manifest entry.
         * Visibility: Guru
         */
        GenApi::IString &DeviceManifestSecondaryURL;

        /**
         * Description: Sub minor version of the Transport Layer of the device.
         * Visibility: Beginner
         */
        GenApi::IInteger &DeviceTLVersionSubMinor;

        /**
         * Description: Major version of the GenCP protocol supported by the device.
         * Visibility: Beginner
         */
        GenApi::IInteger &DeviceGenCPVersionMajor;

        /**
         * Description: Minor version of the GenCP protocol supported by the device.
         * Visibility: Beginner
         */
        GenApi::IInteger &DeviceGenCPVersionMinor;

        /**
         * Description: Selects which Connection of the device to control.
         * Visibility: Beginner
         */
        GenApi::IInteger &DeviceConnectionSelector;

        /**
         * Description: Indicates the speed of transmission of the specified Connection
         * Visibility: Expert
         */
        GenApi::IInteger &DeviceConnectionSpeed;

        /**
         * Description: Indicates the status of the specified Connection.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<DeviceConnectionStatusEnums> &DeviceConnectionStatus;

        /**
         * Description: Selects which Link of the device to control.
         * Visibility: Beginner
         */
        GenApi::IInteger &DeviceLinkSelector;

        /**
         * Description: Controls if the DeviceLinkThroughputLimit is active. When disabled, lower level TL specific features are expected to control the throughput. When enabled, DeviceLinkThroughputLimit controls the overall throughput.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<DeviceLinkThroughputLimitModeEnums> &DeviceLinkThroughputLimitMode;

        /**
         * Description: Returns the number of physical connection of the device used by a particular Link.
         * Visibility: Beginner
         */
        GenApi::IInteger &DeviceLinkConnectionCount;

        /**
         * Description: Activate or deactivate the Link's heartbeat.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<DeviceLinkHeartbeatModeEnums> &DeviceLinkHeartbeatMode;

        /**
         * Description: Controls the current heartbeat timeout of the specific Link.
         * Visibility: Guru
         */
        GenApi::IFloat &DeviceLinkHeartbeatTimeout;

        /**
         * Description: Indicates the command timeout of the specified Link. This corresponds to the maximum response time of the device for a command sent on that link.
         * Visibility: Guru
         */
        GenApi::IFloat &DeviceLinkCommandTimeout;

        /**
         * Description: Selects the stream channel to control.
         * Visibility: Expert
         */
        GenApi::IInteger &DeviceStreamChannelSelector;

        /**
         * Description: Reports the type of the stream channel.
         * Visibility: Guru
         */
        GenApi::IEnumerationT<DeviceStreamChannelTypeEnums> &DeviceStreamChannelType;

        /**
         * Description: Index of device's Link to use for streaming the specifed stream channel.
         * Visibility: Guru
         */
        GenApi::IInteger &DeviceStreamChannelLink;

        /**
         * Description: Endianess of multi-byte pixel data for this stream.
         * Visibility: Guru
         */
        GenApi::IEnumerationT<DeviceStreamChannelEndiannessEnums> &DeviceStreamChannelEndianness;

        /**
         * Description: Specifies the stream packet size, in bytes, to send on the selected channel for a Transmitter or specifies the maximum packet size supported by a receiver.
         * Visibility: Expert
         */
        GenApi::IInteger &DeviceStreamChannelPacketSize;

        /**
         * Description: Indicate to the device and GenICam XML to get ready for persisting of all streamable features.
         * Visibility: Guru
         */
        GenApi::ICommand &DeviceFeaturePersistenceStart;

        /**
         * Description: Indicate to the device the end of feature persistence.
         * Visibility: Guru
         */
        GenApi::ICommand &DeviceFeaturePersistenceEnd;

        /**
         * Description: Prepare the device for registers streaming without checking for consistency.
         * Visibility: Guru
         */
        GenApi::ICommand &DeviceRegistersStreamingStart;

        /**
         * Description: Announce the end of registers streaming. This will do a register set validation for consistency and activate it. This will also update the DeviceRegistersValid flag.
         * Visibility: Guru
         */
        GenApi::ICommand &DeviceRegistersStreamingEnd;

        /**
         * Description: Perform the validation of the current register set for consistency. This will update the DeviceRegistersValid flag.
         * Visibility: Expert
         */
        GenApi::ICommand &DeviceRegistersCheck;

        /**
         * Description: Returns if the current register set is valid and consistent.
         * Visibility: Expert
         */
        GenApi::IBoolean &DeviceRegistersValid;

        /**
         * Description: Selects the clock frequency to access from the device.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<DeviceClockSelectorEnums> &DeviceClockSelector;

        /**
         * Description: Returns the frequency of the selected Clock.
         * Visibility: Expert
         */
        GenApi::IFloat &DeviceClockFrequency;

        /**
         * Description: Selects which serial port of the device to control.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<DeviceSerialPortSelectorEnums> &DeviceSerialPortSelector;

        /**
         * Description: This feature controls the baud rate used by the selected serial port.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<DeviceSerialPortBaudRateEnums> &DeviceSerialPortBaudRate;

        /**
         * Description: Reports the current value of the device timestamp counter.
         * Visibility: Expert
         */
        GenApi::IInteger &Timestamp;

        /**
         * Description: Number of taps of the camera sensor.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<SensorTapsEnums> &SensorTaps;

        /**
         * Description: Number of digitized samples outputted simultaneously by the camera A/D conversion stage.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<SensorDigitizationTapsEnums> &SensorDigitizationTaps;

        /**
         * Description: Selects the Region of interest to control. The RegionSelector feature allows devices that are able to extract multiple regions out of an image, to configure the features of those individual regions independently.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<RegionSelectorEnums> &RegionSelector;

        /**
         * Description: Controls if the selected Region of interest is active and streaming.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<RegionModeEnums> &RegionMode;

        /**
         * Description: Control the destination of the selected region.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<RegionDestinationEnums> &RegionDestination;

        /**
         * Description: Selects a component to activate data streaming from.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<ImageComponentSelectorEnums> &ImageComponentSelector;

        /**
         * Description: Controls if the selected component streaming is active.
         * Visibility: Beginner
         */
        GenApi::IBoolean &ImageComponentEnable;

        /**
         * Description: Total number of bytes between 2 successive lines. This feature is used to facilitate alignment of image data.
         * Visibility: Expert
         */
        GenApi::IInteger &LinePitch;

        /**
         * Description: Select the pixel format for which the information will be returned.
         * Visibility: Guru
         */
        GenApi::IEnumerationT<PixelFormatInfoSelectorEnums> &PixelFormatInfoSelector;

        /**
         * Description: Returns the value used by the streaming channels to identify the selected pixel format.
         * Visibility: Guru
         */
        GenApi::IInteger &PixelFormatInfoID;

        /**
         * Description: Controls how the device performs de-interlacing.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<DeinterlacingEnums> &Deinterlacing;

        /**
         * Description: Two rate controlling options are offered: fixed bit rate or fixed quality. The exact implementation to achieve one or the other is vendor-specific.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ImageCompressionRateOptionEnums> &ImageCompressionRateOption;

        /**
         * Description: Control the quality of the produced compressed stream.
         * Visibility: Expert
         */
        GenApi::IInteger &ImageCompressionQuality;

        /**
         * Description: Control the rate of the produced compressed stream.
         * Visibility: Expert
         */
        GenApi::IFloat &ImageCompressionBitrate;

        /**
         * Description: When JPEG is selected as the compression format, a device might optionally offer better control over JPEG-specific options through this feature.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ImageCompressionJPEGFormatOptionEnums> &ImageCompressionJPEGFormatOption;

        /**
         * Description: Aborts the Acquisition immediately. This will end the capture without completing the current Frame or waiting on a trigger. If no Acquisition is in progress, the command is ignored.
         * Visibility: Expert
         */
        GenApi::ICommand &AcquisitionAbort;

        /**
         * Description: Arms the device before an AcquisitionStart command. This optional command validates all the current features for consistency and prepares the device for a fast start of the Acquisition.
         * Visibility: Expert
         */
        GenApi::ICommand &AcquisitionArm;

        /**
         * Description: Selects the internal acquisition signal to read using AcquisitionStatus.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<AcquisitionStatusSelectorEnums> &AcquisitionStatusSelector;

        /**
         * Description: Reads the state of the internal acquisition signal selected using AcquisitionStatusSelector.
         * Visibility: Expert
         */
        GenApi::IBoolean &AcquisitionStatus;

        /**
         * Description: Specifies a division factor for the incoming trigger pulses.
         * Visibility: Expert
         */
        GenApi::IInteger &TriggerDivider;

        /**
         * Description: Specifies a multiplication factor for the incoming trigger pulses. It is used generally used in conjunction with TriggerDivider to control the ratio of triggers that are accepted.
         * Visibility: Expert
         */
        GenApi::IInteger &TriggerMultiplier;

        /**
         * Description: Sets the configuration mode of the ExposureTime feature.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<ExposureTimeModeEnums> &ExposureTimeMode;

        /**
         * Description: Selects which exposure time is controlled by the ExposureTime feature. This allows for independent control over the exposure components.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<ExposureTimeSelectorEnums> &ExposureTimeSelector;

        /**
         * Description: Sets the mode for automatic gain balancing between the sensor color channels or taps. The gain coefficients of each channel or tap are adjusted so they are matched.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<GainAutoBalanceEnums> &GainAutoBalance;

        /**
         * Description: Controls the mode for automatic black level adjustment. The exact algorithm used to implement this adjustment is device-specific.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<BlackLevelAutoEnums> &BlackLevelAuto;

        /**
         * Description: Controls the mode for automatic black level balancing between the sensor color channels or taps. The black level coefficients of each channel are adjusted so they are matched.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<BlackLevelAutoBalanceEnums> &BlackLevelAutoBalance;

        /**
         * Description: Selects which White Clip to control.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<WhiteClipSelectorEnums> &WhiteClipSelector;

        /**
         * Description: Controls the maximal intensity taken by the video signal before being clipped as an absolute physical value. The video signal will never exceed the white clipping point: it will saturate at that level.
         * Visibility: Expert
         */
        GenApi::IFloat &WhiteClip;

        /**
         * Description: Accesses all the LUT coefficients in a single access without using individual LUTIndex.
         * Visibility: Guru
         */
        GenApi::IRegister &LUTValueAll;

        /**
         * Description: Sets the write mask to apply to the value specified by UserOutputValueAll before writing it in the User Output register. If the UserOutputValueAllMask feature is present, setting the user Output register using UserOutputValueAll will only change the bits that have a corresponding bit in the mask set to one.
         * Visibility: Expert
         */
        GenApi::IInteger &UserOutputValueAllMask;

        /**
         * Description: Does a software reset of the selected Counter and starts it. The counter starts counting events immediately after the reset unless a Counter trigger is active. CounterReset can be used to reset the Counter independently from the CounterResetSource. To disable the counter temporarily, set CounterEventSource to Off.
         * Visibility: Expert
         */
        GenApi::ICommand &CounterReset;

        /**
         * Description: Selects which Timer to configure.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<TimerSelectorEnums> &TimerSelector;

        /**
         * Description: Sets the duration (in microseconds) of the Timer pulse.
         * Visibility: Expert
         */
        GenApi::IFloat &TimerDuration;

        /**
         * Description: Sets the duration (in microseconds) of the delay to apply at the reception of a trigger before starting the Timer.
         * Visibility: Expert
         */
        GenApi::IFloat &TimerDelay;

        /**
         * Description: Does a software reset of the selected timer and starts it. The timer starts immediately after the reset unless a timer trigger is active.
         * Visibility: Expert
         */
        GenApi::ICommand &TimerReset;

        /**
         * Description: Reads or writes the current value (in microseconds) of the selected Timer.
         * Visibility: Expert
         */
        GenApi::IFloat &TimerValue;

        /**
         * Description: Returns the current status of the Timer.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<TimerStatusEnums> &TimerStatus;

        /**
         * Description: Selects the source of the trigger to start the Timer.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<TimerTriggerSourceEnums> &TimerTriggerSource;

        /**
         * Description: Selects the activation mode of the trigger to start the Timer.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<TimerTriggerActivationEnums> &TimerTriggerActivation;

        /**
         * Description: Selects which Encoder to configure.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<EncoderSelectorEnums> &EncoderSelector;

        /**
         * Description: Selects the signal which will be the source of the A input of the Encoder.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<EncoderSourceAEnums> &EncoderSourceA;

        /**
         * Description: Selects the signal which will be the source of the B input of the Encoder.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<EncoderSourceBEnums> &EncoderSourceB;

        /**
         * Description: Selects if the count of encoder uses FourPhase mode with jitter filtering or the HighResolution mode without jitter filtering.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<EncoderModeEnums> &EncoderMode;

        /**
         * Description: Sets how many Encoder increment/decrements that are needed generate an Encoder output pulse signal.
         * Visibility: Expert
         */
        GenApi::IInteger &EncoderDivider;

        /**
         * Description: Selects the conditions for the Encoder interface to generate a valid Encoder output signal.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<EncoderOutputModeEnums> &EncoderOutputMode;

        /**
         * Description: Returns the motion status of the encoder.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<EncoderStatusEnums> &EncoderStatus;

        /**
         * Description: Sets the maximum time interval between encoder counter increments before the status turns to static.
         * Visibility: Expert
         */
        GenApi::IFloat &EncoderTimeout;

        /**
         * Description: Selects the signals that will be the source to reset the Encoder.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<EncoderResetSourceEnums> &EncoderResetSource;

        /**
         * Description: Selects the Activation mode of the Encoder Reset Source signal.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<EncoderResetActivationEnums> &EncoderResetActivation;

        /**
         * Description: Does a software reset of the selected Encoder and starts it. The Encoder starts counting events immediately after the reset. EncoderReset can be used to reset the Encoder independently from the EncoderResetSource.
         * Visibility: Expert
         */
        GenApi::ICommand &EncoderReset;

        /**
         * Description: Reads or writes the current value of the position counter of the selected Encoder.
         * Visibility: Expert
         */
        GenApi::IInteger &EncoderValue;

        /**
         * Description: Reads the value of the of the position counter of the selected Encoder when it was reset by a signal or by an explicit EncoderReset command.
         * Visibility: Expert
         */
        GenApi::IInteger &EncoderValueAtReset;

        /**
         * Description: Selects which Software Signal features to control.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<SoftwareSignalSelectorEnums> &SoftwareSignalSelector;

        /**
         * Description: Generates a pulse signal that can be used as a software trigger. This command can be used to trigger other modules that accept a SoftwareSignal as trigger source.
         * Visibility: Beginner
         */
        GenApi::ICommand &SoftwareSignalPulse;

        /**
         * Description: Enables the unconditional action command mode where action commands are processed even when the primary control channel is closed.
         * Visibility: Guru
         */
        GenApi::IEnumerationT<ActionUnconditionalModeEnums> &ActionUnconditionalMode;

        /**
         * Description: Provides the device key that allows the device to check the validity of action commands. The device internal assertion of an action signal is only authorized if the ActionDeviceKey and the action device key value in the protocol message are equal.
         * Visibility: Guru
         */
        GenApi::IInteger &ActionDeviceKey;

        /**
         * Description: Indicates the size of the scheduled action commands queue. This number represents the maximum number of scheduled action commands that can be pending at a given point in time.
         * Visibility: Guru
         */
        GenApi::IInteger &ActionQueueSize;

        /**
         * Description: Selects to which Action Signal further Action settings apply.
         * Visibility: Guru
         */
        GenApi::IInteger &ActionSelector;

        /**
         * Description: Provides the mask that the device will use to validate the action on reception of the action protocol message.
         * Visibility: Guru
         */
        GenApi::IInteger &ActionGroupMask;

        /**
         * Description: Provides the key that the device will use to validate the action on reception of the action protocol message.
         * Visibility: Guru
         */
        GenApi::IInteger &ActionGroupKey;

        /**
         * Description: Returns the unique Identifier of the Acquisition Trigger type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionTrigger;

        /**
         * Description: Returns the Timestamp of the Acquisition Trigger Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionTriggerTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Acquisition Trigger Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionTriggerFrameID;

        /**
         * Description: Returns the unique Identifier of the Acquisition Start type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionStart;

        /**
         * Description: Returns the Timestamp of the Acquisition Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionStartTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Acquisition Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionStartFrameID;

        /**
         * Description: Returns the unique Identifier of the Acquisition End type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionEnd;

        /**
         * Description: Returns the Timestamp of the Acquisition End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionEndTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Acquisition End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionEndFrameID;

        /**
         * Description: Returns the unique Identifier of the Acquisition Transfer Start type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionTransferStart;

        /**
         * Description: Returns the Timestamp of the Acquisition Transfer Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionTransferStartTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Acquisition Transfer Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionTransferStartFrameID;

        /**
         * Description: Returns the unique Identifier of the Acquisition Transfer End type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionTransferEnd;

        /**
         * Description: Returns the Timestamp of the Acquisition Transfer End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionTransferEndTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Acquisition Transfer End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionTransferEndFrameID;

        /**
         * Description: Returns the unique Identifier of the Acquisition Error type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionError;

        /**
         * Description: Returns the Timestamp of the Acquisition Error Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionErrorTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Acquisition Error Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventAcquisitionErrorFrameID;

        /**
         * Description: Returns the unique Identifier of the FrameTrigger type of Event. It can be used to register a callback function to be notified of the event occurrence. Its value uniquely identifies the type event received.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameTrigger;

        /**
         * Description: Returns the Timestamp of the FrameTrigger Event. It can be used to determine precisely when the event occurred.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameTriggerTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the FrameTrigger Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameTriggerFrameID;

        /**
         * Description: Returns the unique Identifier of the Frame Start type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameStart;

        /**
         * Description: Returns the Timestamp of the Frame Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameStartTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Frame Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameStartFrameID;

        /**
         * Description: Returns the unique Identifier of the Frame End type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameEnd;

        /**
         * Description: Returns the Timestamp of the Frame End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameEndTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Frame End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameEndFrameID;

        /**
         * Description: Returns the unique Identifier of the Frame Burst Start type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameBurstStart;

        /**
         * Description: Returns the Timestamp of the Frame Burst Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameBurstStartTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Frame Burst Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameBurstStartFrameID;

        /**
         * Description: Returns the unique Identifier of the Frame Burst End type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameBurstEnd;

        /**
         * Description: Returns the Timestamp of the Frame Burst End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameBurstEndTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Frame Burst End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameBurstEndFrameID;

        /**
         * Description: Returns the unique Identifier of the Frame Transfer Start type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameTransferStart;

        /**
         * Description: Returns the Timestamp of the Frame Transfer Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameTransferStartTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Frame Transfer Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameTransferStartFrameID;

        /**
         * Description: Returns the unique Identifier of the Frame Transfer End type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameTransferEnd;

        /**
         * Description: Returns the Timestamp of the Frame Transfer End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameTransferEndTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Frame Transfer End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventFrameTransferEndFrameID;

        /**
         * Description: Returns the unique Identifier of the Exposure Start type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventExposureStart;

        /**
         * Description: Returns the Timestamp of the Exposure Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventExposureStartTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Exposure Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventExposureStartFrameID;

        /**
         * Description: Returns the unique Identifier of the Stream 0 Transfer Start type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferStart;

        /**
         * Description: Returns the Timestamp of the Stream 0 Transfer Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferStartTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferStartFrameID;

        /**
         * Description: Returns the unique Identifier of the Stream 0 Transfer End type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferEnd;

        /**
         * Description: Returns the Timestamp of the Stream 0 Transfer End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferEndTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferEndFrameID;

        /**
         * Description: Returns the unique Identifier of the Stream 0 Transfer Pause type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferPause;

        /**
         * Description: Returns the Timestamp of the Stream 0 Transfer Pause Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferPauseTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Pause Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferPauseFrameID;

        /**
         * Description: Returns the unique Identifier of the Stream 0 Transfer Resume type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferResume;

        /**
         * Description: Returns the Timestamp of the Stream 0 Transfer Resume Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferResumeTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Resume Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferResumeFrameID;

        /**
         * Description: Returns the unique Identifier of the Stream 0 Transfer Block Start type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBlockStart;

        /**
         * Description: Returns the Timestamp of the Stream 0 Transfer Block Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBlockStartTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Block Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBlockStartFrameID;

        /**
         * Description: Returns the unique Identifier of the Stream 0 Transfer Block End type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBlockEnd;

        /**
         * Description: Returns the Timestamp of the Stream 0 Transfer Block End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBlockEndTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Block End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBlockEndFrameID;

        /**
         * Description: Returns the unique Identifier of the Stream 0 Transfer Block Trigger type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBlockTrigger;

        /**
         * Description: Returns the Timestamp of the Stream 0 Transfer Block Trigger Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBlockTriggerTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Block Trigger Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBlockTriggerFrameID;

        /**
         * Description: Returns the unique Identifier of the Stream 0 Transfer Burst Start type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBurstStart;

        /**
         * Description: Returns the Timestamp of the Stream 0 Transfer Burst Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBurstStartTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Burst Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBurstStartFrameID;

        /**
         * Description: Returns the unique Identifier of the Stream 0 Transfer Burst End type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBurstEnd;

        /**
         * Description: Returns the Timestamp of the Stream 0 Transfer Burst End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBurstEndTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Burst End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferBurstEndFrameID;

        /**
         * Description: Returns the unique Identifier of the Stream 0 Transfer Overflow type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferOverflow;

        /**
         * Description: Returns the Timestamp of the Stream 0 Transfer Overflow Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferOverflowTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Stream 0 Transfer Overflow Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventStream0TransferOverflowFrameID;

        /**
         * Description: Returns the unique Identifier of the Sequencer Set Change type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventSequencerSetChange;

        /**
         * Description: Returns the Timestamp of the Sequencer Set Change Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventSequencerSetChangeTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Sequencer Set Change Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventSequencerSetChangeFrameID;

        /**
         * Description: Returns the unique Identifier of the Counter 0 Start type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventCounter0Start;

        /**
         * Description: Returns the Timestamp of the Counter 0 Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventCounter0StartTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Counter 0 Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventCounter0StartFrameID;

        /**
         * Description: Returns the unique Identifier of the Counter 1 Start type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventCounter1Start;

        /**
         * Description: Returns the Timestamp of the Counter 1 Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventCounter1StartTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Counter 1 Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventCounter1StartFrameID;

        /**
         * Description: Returns the unique Identifier of the Counter 0 End type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventCounter0End;

        /**
         * Description: Returns the Timestamp of the Counter 0 End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventCounter0EndTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Counter 0 End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventCounter0EndFrameID;

        /**
         * Description: Returns the unique Identifier of the Counter 1 End type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventCounter1End;

        /**
         * Description: Returns the Timestamp of the Counter 1 End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventCounter1EndTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Counter 1 End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventCounter1EndFrameID;

        /**
         * Description: Returns the unique Identifier of the Timer 0 Start type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventTimer0Start;

        /**
         * Description: Returns the Timestamp of the Timer 0 Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventTimer0StartTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Timer 0 Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventTimer0StartFrameID;

        /**
         * Description: Returns the unique Identifier of the Timer 1 Start type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventTimer1Start;

        /**
         * Description: Returns the Timestamp of the Timer 1 Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventTimer1StartTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Timer 1 Start Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventTimer1StartFrameID;

        /**
         * Description: Returns the unique Identifier of the Timer 0 End type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventTimer0End;

        /**
         * Description: Returns the Timestamp of the Timer 0 End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventTimer0EndTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Timer 0 End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventTimer0EndFrameID;

        /**
         * Description: Returns the unique Identifier of the Timer 1 End type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventTimer1End;

        /**
         * Description: Returns the Timestamp of the Timer 1 End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventTimer1EndTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Timer 1 End Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventTimer1EndFrameID;

        /**
         * Description: Returns the unique Identifier of the Encoder 0 Stopped type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventEncoder0Stopped;

        /**
         * Description: Returns the Timestamp of the Encoder 0 Stopped Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventEncoder0StoppedTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Encoder 0 Stopped Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventEncoder0StoppedFrameID;

        /**
         * Description: Returns the unique Identifier of the Encoder 1 Stopped type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventEncoder1Stopped;

        /**
         * Description: Returns the Timestamp of the Encoder 1 Stopped Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventEncoder1StoppedTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Encoder 1 Stopped Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventEncoder1StoppedFrameID;

        /**
         * Description: Returns the unique Identifier of the Encoder 0 Restarted type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventEncoder0Restarted;

        /**
         * Description: Returns the Timestamp of the Encoder 0 Restarted Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventEncoder0RestartedTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Encoder 0 Restarted Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventEncoder0RestartedFrameID;

        /**
         * Description: Returns the unique Identifier of the Encoder 1 Restarted type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventEncoder1Restarted;

        /**
         * Description: Returns the Timestamp of the Encoder 1 Restarted Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventEncoder1RestartedTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Encoder 1 Restarted Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventEncoder1RestartedFrameID;

        /**
         * Description: Returns the unique Identifier of the Line 0 Rising Edge type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine0RisingEdge;

        /**
         * Description: Returns the Timestamp of the Line 0 Rising Edge Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine0RisingEdgeTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Line 0 Rising Edge Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine0RisingEdgeFrameID;

        /**
         * Description: Returns the unique Identifier of the Line 1 Rising Edge type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine1RisingEdge;

        /**
         * Description: Returns the Timestamp of the Line 1 Rising Edge Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine1RisingEdgeTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Line 1 Rising Edge Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine1RisingEdgeFrameID;

        /**
         * Description: Returns the unique Identifier of the Line 0 Falling Edge type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine0FallingEdge;

        /**
         * Description: Returns the Timestamp of the Line 0 Falling Edge Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine0FallingEdgeTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Line 0 Falling Edge Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine0FallingEdgeFrameID;

        /**
         * Description: Returns the unique Identifier of the Line 1 Falling Edge type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine1FallingEdge;

        /**
         * Description: Returns the Timestamp of the Line 1 Falling Edge Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine1FallingEdgeTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Line 1 Falling Edge Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine1FallingEdgeFrameID;

        /**
         * Description: Returns the unique Identifier of the Line 0 Any Edge type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine0AnyEdge;

        /**
         * Description: Returns the Timestamp of the Line 0 Any Edge Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine0AnyEdgeTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Line 0 Any Edge Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine0AnyEdgeFrameID;

        /**
         * Description: Returns the unique Identifier of the Line 1 Any Edge type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine1AnyEdge;

        /**
         * Description: Returns the Timestamp of the Line 1 Any Edge Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine1AnyEdgeTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Line 1 Any Edge Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLine1AnyEdgeFrameID;

        /**
         * Description: Returns the unique Identifier of the Link Trigger 0 type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLinkTrigger0;

        /**
         * Description: Returns the Timestamp of the Link Trigger 0 Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLinkTrigger0Timestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Link Trigger 0 Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLinkTrigger0FrameID;

        /**
         * Description: Returns the unique Identifier of the Link Trigger 1 type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLinkTrigger1;

        /**
         * Description: Returns the Timestamp of the Link Trigger 1 Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLinkTrigger1Timestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Link Trigger 1 Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLinkTrigger1FrameID;

        /**
         * Description: Returns the unique Identifier of the Action Late type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventActionLate;

        /**
         * Description: Returns the Timestamp of the Action Late Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventActionLateTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Action Late Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventActionLateFrameID;

        /**
         * Description: Returns the unique Identifier of the Link Speed Change type of Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLinkSpeedChange;

        /**
         * Description: Returns the Timestamp of the Link Speed Change Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLinkSpeedChangeTimestamp;

        /**
         * Description: Returns the unique Identifier of the Frame (or image) that generated the Link Speed Change Event.
         * Visibility: Expert
         */
        GenApi::IInteger &EventLinkSpeedChangeFrameID;

        /**
         * Description: Defines the intermediate access buffer that allows the exchange of data between the device file storage and the application.
         * Visibility: Guru
         */
        GenApi::IRegister &FileAccessBuffer;

        /**
         * Description: Controls or returns the number of sources supported by the device.
         * Visibility: Beginner
         */
        GenApi::IInteger &SourceCount;

        /**
         * Description: Selects the source to control.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<SourceSelectorEnums> &SourceSelector;

        /**
         * Description: Selects which stream transfers are currently controlled by the selected Transfer features.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<TransferSelectorEnums> &TransferSelector;

        /**
         * Description: Number of Block(s) to transfer for each TransferBurstStart trigger.
         * Visibility: Expert
         */
        GenApi::IInteger &TransferBurstCount;

        /**
         * Description: Aborts immediately the streaming of data block(s). Aborting the transfer will result in the lost of the data that is present or currently entering in the block queue. However, the next new block received will be stored in the queue and transferred to the host when the streaming is restarted. If implemented, this feature should be available when the TransferControlMode is set to "UserControlled".
         * Visibility: Expert
         */
        GenApi::ICommand &TransferAbort;

        /**
         * Description: Pauses the streaming of data Block(s). Pausing the streaming will immediately suspend the ongoing data transfer even if a block is partially transfered. The device will resume its transmission at the reception of a TransferResume command.
         * Visibility: Guru
         */
        GenApi::ICommand &TransferPause;

        /**
         * Description: Resumes a data Blocks streaming that was previously paused by a TransferPause command.
         * Visibility: Guru
         */
        GenApi::ICommand &TransferResume;

        /**
         * Description: Selects the type of transfer trigger to configure.
         * Visibility: Guru
         */
        GenApi::IEnumerationT<TransferTriggerSelectorEnums> &TransferTriggerSelector;

        /**
         * Description: Controls if the selected trigger is active.
         * Visibility: Guru
         */
        GenApi::IEnumerationT<TransferTriggerModeEnums> &TransferTriggerMode;

        /**
         * Description: Specifies the signal to use as the trigger source for transfers.
         * Visibility: Guru
         */
        GenApi::IEnumerationT<TransferTriggerSourceEnums> &TransferTriggerSource;

        /**
         * Description: Specifies the activation mode of the transfer control trigger.
         * Visibility: Guru
         */
        GenApi::IEnumerationT<TransferTriggerActivationEnums> &TransferTriggerActivation;

        /**
         * Description: Selects which status of the transfer module to read.
         * Visibility: Guru
         */
        GenApi::IEnumerationT<TransferStatusSelectorEnums> &TransferStatusSelector;

        /**
         * Description: Reads the status of the Transfer module signal selected by TransferStatusSelector.
         * Visibility: Guru
         */
        GenApi::IBoolean &TransferStatus;

        /**
         * Description: Selects the color component for the control of the TransferStreamChannel feature.
         * Visibility: Guru
         */
        GenApi::IEnumerationT<TransferComponentSelectorEnums> &TransferComponentSelector;

        /**
         * Description: Selects the streaming channel that will be used to transfer the selected stream of data. In general, this feature can be omitted and the default streaming channel will be used.
         * Visibility: Guru
         */
        GenApi::IInteger &TransferStreamChannel;

        /**
         * Description: Specifies the unit used when delivering calibrated distance data.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<Scan3dDistanceUnitEnums> &Scan3dDistanceUnit;

        /**
         * Description: Specifies the Coordinate system to use for the device.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<Scan3dCoordinateSystemEnums> &Scan3dCoordinateSystem;

        /**
         * Description: Controls the Calibration and data organization of the device, naming the coordinates transmitted.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<Scan3dOutputModeEnums> &Scan3dOutputMode;

        /**
         * Description: Defines coordinate system reference location.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<Scan3dCoordinateSystemReferenceEnums> &Scan3dCoordinateSystemReference;

        /**
         * Description: Selects the individual coordinates in the vectors for 3D information/transformation.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<Scan3dCoordinateSelectorEnums> &Scan3dCoordinateSelector;

        /**
         * Description: Scale factor when transforming a pixel from relative coordinates to world coordinates.
         * Visibility: Expert
         */
        GenApi::IFloat &Scan3dCoordinateScale;

        /**
         * Description: Offset when transforming a pixel from relative coordinates to world coordinates.
         * Visibility: Expert
         */
        GenApi::IFloat &Scan3dCoordinateOffset;

        /**
         * Description: Enables the definition of a non-valid flag value in the data stream. Note that the confidence output is an alternate recommended way to identify non-valid pixels. Using an Scan3dInvalidDataValue may give processing penalties due to special handling.
         * Visibility: Expert
         */
        GenApi::IBoolean &Scan3dInvalidDataFlag;

        /**
         * Description: Value which identifies a non-valid pixel if Scan3dInvalidDataFlag is enabled.
         * Visibility: Expert
         */
        GenApi::IFloat &Scan3dInvalidDataValue;

        /**
         * Description: Minimum valid transmitted coordinate value of the selected Axis.
         * Visibility: Expert
         */
        GenApi::IFloat &Scan3dAxisMin;

        /**
         * Description: Maximum valid transmitted coordinate value of the selected Axis.
         * Visibility: Expert
         */
        GenApi::IFloat &Scan3dAxisMax;

        /**
         * Description: Sets the index to read/write a coordinate transform value.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<Scan3dCoordinateTransformSelectorEnums> &Scan3dCoordinateTransformSelector;

        /**
         * Description: Specifies the transform value selected. For translations (Scan3dCoordinateTransformSelector = TranslationX/Y/Z) it is expressed in the distance unit of the system, for rotations (Scan3dCoordinateTransformSelector =RotationX/Y/Z) in degrees.
         * Visibility: Expert
         */
        GenApi::IFloat &Scan3dTransformValue;

        /**
         * Description: Sets the index to read a coordinate system reference value defining the transform of a point from the current (Anchor or Transformed) system to the reference system.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<Scan3dCoordinateReferenceSelectorEnums> &Scan3dCoordinateReferenceSelector;

        /**
         * Description: Returns the reference value selected. Reads the value of a rotation or translation value for the current (Anchor or Transformed) coordinate system transformation to the Reference system.
         * Visibility: Expert
         */
        GenApi::IFloat &Scan3dCoordinateReferenceValue;

        /**
         * Description: Selects the part to access in chunk data in a multipart transmission.
         * Visibility: Expert
         */
        GenApi::IInteger &ChunkPartSelector;

        /**
         * Description: Returns the component of the payload image. This can be used to identify the image component of a generic part in a multipart transfer.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkImageComponentEnums> &ChunkImageComponent;

        /**
         * Description: Returns the minimum value of dynamic range of the image included in the payload.
         * Visibility: Expert
         */
        GenApi::IInteger &ChunkPixelDynamicRangeMin;

        /**
         * Description: Returns the maximum value of dynamic range of the image included in the payload.
         * Visibility: Expert
         */
        GenApi::IInteger &ChunkPixelDynamicRangeMax;

        /**
         * Description: Returns the last Timestamp latched with the TimestampLatch command.
         * Visibility: Expert
         */
        GenApi::IInteger &ChunkTimestampLatchValue;

        /**
         * Description: Returns the status of all the I/O lines at the time of the FrameStart internal event.
         * Visibility: Expert
         */
        GenApi::IInteger &ChunkLineStatusAll;

        /**
         * Description: Selects which counter to retrieve data from.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkCounterSelectorEnums> &ChunkCounterSelector;

        /**
         * Description: Returns the value of the selected Chunk counter at the time of the FrameStart event.
         * Visibility: Expert
         */
        GenApi::IInteger &ChunkCounterValue;

        /**
         * Description: Selects which Timer to retrieve data from.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkTimerSelectorEnums> &ChunkTimerSelector;

        /**
         * Description: Returns the value of the selected Timer at the time of the FrameStart internal event.
         * Visibility: Expert
         */
        GenApi::IFloat &ChunkTimerValue;

        /**
         * Description: Selects which Encoder to retrieve data from.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkEncoderSelectorEnums> &ChunkEncoderSelector;

        /**
         * Description: Index for vector representation of one chunk value per line in an image.
         * Visibility: Expert
         */
        GenApi::IInteger &ChunkScanLineSelector;

        /**
         * Description: Returns the counter's value of the selected Encoder at the time of the FrameStart in area scan mode or the counter's value at the time of the LineStart selected by ChunkScanLineSelector in LineScan mode.
         * Visibility: Expert
         */
        GenApi::IInteger &ChunkEncoderValue;

        /**
         * Description: Returns the motion status of the selected encoder.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkEncoderStatusEnums> &ChunkEncoderStatus;

        /**
         * Description: Selects which exposure time is read by the ChunkExposureTime feature.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkExposureTimeSelectorEnums> &ChunkExposureTimeSelector;

        /**
         * Description: Returns the LinePitch of the image included in the payload.
         * Visibility: Expert
         */
        GenApi::IInteger &ChunkLinePitch;

        /**
         * Description: Returns the identifier of Source that the image comes from.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkSourceIDEnums> &ChunkSourceID;

        /**
         * Description: Returns the identifier of Region that the image comes from.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkRegionIDEnums> &ChunkRegionID;

        /**
         * Description: Returns the unique identifier of the transfer block used to transport the payload.
         * Visibility: Expert
         */
        GenApi::IInteger &ChunkTransferBlockID;

        /**
         * Description: Returns identifier of the stream that generated this block.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkTransferStreamIDEnums> &ChunkTransferStreamID;

        /**
         * Description: Returns the current number of blocks in the transfer queue.
         * Visibility: Expert
         */
        GenApi::IInteger &ChunkTransferQueueCurrentBlockCount;

        /**
         * Description: Returns identifier of the stream channel used to carry the block.
         * Visibility: Expert
         */
        GenApi::IInteger &ChunkStreamChannelID;

        /**
         * Description: Returns the Distance Unit of the payload image.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkScan3dDistanceUnitEnums> &ChunkScan3dDistanceUnit;

        /**
         * Description: Returns the Calibrated Mode of the payload image.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkScan3dOutputModeEnums> &ChunkScan3dOutputMode;

        /**
         * Description: Returns the Coordinate System of the image included in the payload.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkScan3dCoordinateSystemEnums> &ChunkScan3dCoordinateSystem;

        /**
         * Description: Returns the Coordinate System Position of the image included in the payload.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkScan3dCoordinateSystemReferenceEnums> &ChunkScan3dCoordinateSystemReference;

        /**
         * Description: Selects which Coordinate to retrieve data from.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkScan3dCoordinateSelectorEnums> &ChunkScan3dCoordinateSelector;

        /**
         * Description: Returns the Scale for the selected coordinate axis of the image included in the payload.
         * Visibility: Expert
         */
        GenApi::IFloat &ChunkScan3dCoordinateScale;

        /**
         * Description: Returns the Offset for the selected coordinate axis of the image included in the payload.
         * Visibility: Expert
         */
        GenApi::IFloat &ChunkScan3dCoordinateOffset;

        /**
         * Description: Returns if a specific non-valid data flag is used in the data stream.
         * Visibility: Expert
         */
        GenApi::IBoolean &ChunkScan3dInvalidDataFlag;

        /**
         * Description: Returns the Invalid Data Value used for the image included in the payload.
         * Visibility: Expert
         */
        GenApi::IFloat &ChunkScan3dInvalidDataValue;

        /**
         * Description: Returns the Minimum Axis value for the selected coordinate axis of the image included in the payload.
         * Visibility: Expert
         */
        GenApi::IFloat &ChunkScan3dAxisMin;

        /**
         * Description: Returns the Maximum Axis value for the selected coordinate axis of the image included in the payload.
         * Visibility: Expert
         */
        GenApi::IFloat &ChunkScan3dAxisMax;

        /**
         * Description: Selector for transform values.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkScan3dCoordinateTransformSelectorEnums> &ChunkScan3dCoordinateTransformSelector;

        /**
         * Description: Returns the transform value.
         * Visibility: Expert
         */
        GenApi::IFloat &ChunkScan3dTransformValue;

        /**
         * Description: Selector to read a coordinate system reference value defining the transform of a point from one system to the other.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ChunkScan3dCoordinateReferenceSelectorEnums> &ChunkScan3dCoordinateReferenceSelector;

        /**
         * Description: Reads the value of a position or pose coordinate for the anchor or transformed coordinate systems relative to the reference point.
         * Visibility: Expert
         */
        GenApi::IFloat &ChunkScan3dCoordinateReferenceValue;

        /**
         * Description: Tests the device's pending acknowledge feature. When this feature is written, the device waits a time period corresponding to the value of TestPendingAck before acknowledging the write.
         * Visibility: Guru
         */
        GenApi::IInteger &TestPendingAck;

        /**
         * Description: This device tap geometry feature describes the geometrical properties characterizing the taps of a camera as presented at the output of the device.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<DeviceTapGeometryEnums> &DeviceTapGeometry;

        /**
         * Description: Controls the principal physical link configuration to use on next restart/power-up of the device.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<GevPhysicalLinkConfigurationEnums> &GevPhysicalLinkConfiguration;

        /**
         * Description: Indicates the current physical link configuration of the device.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<GevCurrentPhysicalLinkConfigurationEnums> &GevCurrentPhysicalLinkConfiguration;

        /**
         * Description: Indicates the current number of active logical links.
         * Visibility: Expert
         */
        GenApi::IInteger &GevActiveLinkCount;

        /**
         * Description: Controls whether incoming PAUSE Frames are handled on the given logical link.
         * Visibility: Expert
         */
        GenApi::IBoolean &GevPAUSEFrameReception;

        /**
         * Description: Controls whether PAUSE Frames can be generated on the given logical link.
         * Visibility: Expert
         */
        GenApi::IBoolean &GevPAUSEFrameTransmission;

        /**
         * Description: Reports the current IP configuration status.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<GevIPConfigurationStatusEnums> &GevIPConfigurationStatus;

        /**
         * Description: Indicates the maximum randomized delay the device will wait to acknowledge a discovery command.
         * Visibility: Expert
         */
        GenApi::IInteger &GevDiscoveryAckDelay;

        /**
         * Description: Selects the GigE Vision version to control extended status codes for.
         * Visibility: Guru
         */
        GenApi::IEnumerationT<GevGVCPExtendedStatusCodesSelectorEnums> &GevGVCPExtendedStatusCodesSelector;

        /**
         * Description: Enables the generation of extended status codes.
         * Visibility: Guru
         */
        GenApi::IBoolean &GevGVCPExtendedStatusCodes;

        /**
         * Description: Controls the key to use to authenticate primary application switchover requests.
         * Visibility: Guru
         */
        GenApi::IInteger &GevPrimaryApplicationSwitchoverKey;

        /**
         * Description: Enables the extended IDs mode.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<GevGVSPExtendedIDModeEnums> &GevGVSPExtendedIDMode;

        /**
         * Description: Returns the UDP source port of the primary application.
         * Visibility: Guru
         */
        GenApi::IInteger &GevPrimaryApplicationSocket;

        /**
         * Description: Returns the address of the primary application.
         * Visibility: Guru
         */
        GenApi::IInteger &GevPrimaryApplicationIPAddress;

        /**
         * Description: Enables the alternate IP destination for stream packets resent due to a packet resend request. When True, the source IP address provided in the packet resend command packet is used. When False, the value set in the GevSCDA[GevStreamChannelSelector] feature is used.
         * Visibility: Guru
         */
        GenApi::IBoolean &GevSCCFGPacketResendDestination;

        /**
         * Description: Enables the selected GVSP transmitter to use the single packet per data block All-in Transmission mode.
         * Visibility: Guru
         */
        GenApi::IBoolean &GevSCCFGAllInTransmission;

        /**
         * Description: Reports the number of zones per block transmitted on the selected stream channel.
         * Visibility: Guru
         */
        GenApi::IInteger &GevSCZoneCount;

        /**
         * Description: Reports the transmission direction of each zone transmitted on the selected stream channel.
         * Visibility: Guru
         */
        GenApi::IInteger &GevSCZoneDirectionAll;

        /**
         * Description: Controls whether the selected stream channel multi-zone configuration is locked. When locked, the GVSP transmitter is not allowed to change the number of zones and their direction during block acquisition and transmission.
         * Visibility: Guru
         */
        GenApi::IBoolean &GevSCZoneConfigurationLock;

        /**
         * Description: Reports the number of transmitted PAUSE frames.
         * Visibility: Guru
         */
        GenApi::IInteger &aPAUSEMACCtrlFramesTransmitted;

        /**
         * Description: Reports the number of received PAUSE frames.
         * Visibility: Guru
         */
        GenApi::IInteger &aPAUSEMACCtrlFramesReceived;

        /**
         * Description: This Camera Link specific feature describes the configuration used by the camera. It helps especially when a camera is capable of operation in a non-standard configuration, and when the features PixelSize, SensorDigitizationTaps, and DeviceTapGeometry do not provide enough information for interpretation of the image data provided by the camera.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<ClConfigurationEnums> &ClConfiguration;

        /**
         * Description: This Camera Link specific feature describes the time multiplexing of the camera link connection to transfer more than the configuration allows, in one single clock.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<ClTimeSlotsCountEnums> &ClTimeSlotsCount;

        /**
         * Description: This feature indicates the current and active Link configuration used by the Device.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<CxpLinkConfigurationStatusEnums> &CxpLinkConfigurationStatus;

        /**
         * Description: Provides the Link configuration that allows the Transmitter Device to operate in its default mode.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<CxpLinkConfigurationPreferredEnums> &CxpLinkConfigurationPreferred;

        /**
         * Description: This feature allows specifying the Link configuration for the communication between the Receiver and Transmitter Device. In most cases this feature does not need to be written because automatic discovery will set configuration correctly to the value returned by CxpLinkConfigurationPreferred. Note that the currently active configuration of the Link can be read using CxpLinkConfigurationStatus.
         * Visibility: Beginner
         */
        GenApi::IEnumerationT<CxpLinkConfigurationEnums> &CxpLinkConfiguration;

        /**
         * Description: Selects the CoaXPress physical connection to control.
         * Visibility: Expert
         */
        GenApi::IInteger &CxpConnectionSelector;

        /**
         * Description: Enables the test mode for an individual physical connection of the Device.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<CxpConnectionTestModeEnums> &CxpConnectionTestMode;

        /**
         * Description: Reports the current connection error count for test packets recieved by the device on the connection selected by CxpConnectionSelector.
         * Visibility: Expert
         */
        GenApi::IInteger &CxpConnectionTestErrorCount;

        /**
         * Description: Reports the current count for test packets recieved by the device on the connection selected by CxpConnectionSelector.
         * Visibility: Expert
         */
        GenApi::IInteger &CxpConnectionTestPacketCount;

        /**
         * Description: Activate automatic control of the Power over CoaXPress (PoCXP) for the Link.
         * Visibility: Expert
         */
        GenApi::ICommand &CxpPoCxpAuto;

        /**
         * Description: Disable Power over CoaXPress (PoCXP) for the Link.
         * Visibility: Expert
         */
        GenApi::ICommand &CxpPoCxpTurnOff;

        /**
         * Description: Reset the Power over CoaXPress (PoCXP) Link after an over-current trip on the Device connection(s).
         * Visibility: Expert
         */
        GenApi::ICommand &CxpPoCxpTripReset;

        /**
         * Description: Returns the Power over CoaXPress (PoCXP) status of the Device.
         * Visibility: Expert
         */
        GenApi::IEnumerationT<CxpPoCxpStatusEnums> &CxpPoCxpStatus;

        /**
         * Description: Returns the frame ID associated with the most recent inference result.
         * Visibility: Expert
         */
        GenApi::IInteger &ChunkInferenceFrameId;

        /**
         * Description: Returns the chunk data inference result.
         * Visibility: Expert
         */
        GenApi::IInteger &ChunkInferenceResult;

        /**
         * Description: Returns the chunk data inference confidence percentage.
         * Visibility: Expert
         */
        GenApi::IFloat &ChunkInferenceConfidence;

        /**
         * Description: Returns the chunk inference bounding box result data.
         * Visibility: Expert
         */
        GenApi::IRegister &ChunkInferenceBoundingBoxResult;

    };
    /*@}*/

    /*@}*/

}
#endif // FLIR_SPINNAKER_CAMERA_H