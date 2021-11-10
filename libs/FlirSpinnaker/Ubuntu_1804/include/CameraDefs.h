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

#ifndef FLIR_SPINNAKER_CAMERA_DEFS_H
#define FLIR_SPINNAKER_CAMERA_DEFS_H

namespace Spinnaker
{
    /**
    * @defgroup SpinnakerClasses Spinnaker Classes
    */
    /*@{*/

    /**
    * @defgroup CameraDefs_h CameraDefs Class
    */
    /*@{*/

    /**
    *@brief The enum definitions for camera nodes from the Standard Feature Naming Convention (SFNC) .xml files.
    */

    enum LUTSelectorEnums    /*!< 
      Selects which LUT to control.
    */
    {
        LUTSelector_LUT1,    /*!< 
        This LUT is for re-mapping pixels of all formats 
        (mono, Bayer, red, green and blue).
      */
        NUM_LUTSELECTOR
    };

    enum ExposureModeEnums    /*!< 
      Sets the operation mode of the Exposure.
    */
    {
        ExposureMode_Timed,    /*!< 
        Timed exposure. The exposure time is set using the 
        ExposureTime or ExposureAuto features and the exposure starts with the
        FrameStart or LineStart.
      */
        ExposureMode_TriggerWidth,    /*!< 
        Uses the width of the current Frame trigger signal pulse to control the
        exposure time.
      */
        NUM_EXPOSUREMODE
    };

    enum AcquisitionModeEnums    /*!< Sets the acquisition mode of the device. Continuous: acquires images continuously. Multi Frame: acquires a specified number of images before stopping acquisition. Single Frame: acquires 1 image before stopping acquisition. */
    {
        AcquisitionMode_Continuous,    /*!< */
        AcquisitionMode_SingleFrame,    /*!< */
        AcquisitionMode_MultiFrame,    /*!< */
        NUM_ACQUISITIONMODE
    };

    enum TriggerSourceEnums    /*!< 
      Specifies the internal signal or physical input line to use as the 
      trigger source. 
    */
    {
        TriggerSource_Software,    /*!< */
        TriggerSource_Line0,    /*!< */
        TriggerSource_Line1,    /*!< */
        TriggerSource_Line2,    /*!< */
        TriggerSource_Line3,    /*!< */
        TriggerSource_UserOutput0,    /*!< */
        TriggerSource_UserOutput1,    /*!< */
        TriggerSource_UserOutput2,    /*!< */
        TriggerSource_UserOutput3,    /*!< */
        TriggerSource_Counter0Start,    /*!< */
        TriggerSource_Counter1Start,    /*!< */
        TriggerSource_Counter0End,    /*!< */
        TriggerSource_Counter1End,    /*!< */
        TriggerSource_LogicBlock0,    /*!< */
        TriggerSource_LogicBlock1,    /*!< */
        TriggerSource_Action0,    /*!< */
        NUM_TRIGGERSOURCE
    };

    enum TriggerActivationEnums    /*!< Specifies the activation mode of the trigger.*/
    {
        TriggerActivation_LevelLow,    /*!< */
        TriggerActivation_LevelHigh,    /*!< */
        TriggerActivation_FallingEdge,    /*!< */
        TriggerActivation_RisingEdge,    /*!< */
        TriggerActivation_AnyEdge,    /*!< */
        NUM_TRIGGERACTIVATION
    };

    enum SensorShutterModeEnums    /*!< Sets the shutter mode of the device.*/
    {
        SensorShutterMode_Global,    /*!< 
        The shutter opens and closes at the same time for all pixels.
        All the pixels are exposed for the same length of time at the same time.
      */
        SensorShutterMode_Rolling,    /*!< 
        The shutter opens and closes sequentially for groups (typically lines) of pixels.
        All the pixels are exposed for the same length of time but not at the same time.
      */
        SensorShutterMode_GlobalReset,    /*!< 
        The shutter opens at the same time for all pixels but ends in a sequential manner.
        The pixels are exposed for different lengths of time.
      */
        NUM_SENSORSHUTTERMODE
    };

    enum TriggerModeEnums    /*!< 
      Controls whether or not trigger is active.
    */
    {
        TriggerMode_Off,    /*!< */
        TriggerMode_On,    /*!< */
        NUM_TRIGGERMODE
    };

    enum TriggerOverlapEnums    /*!< Specifies the overlap mode of the trigger.*/
    {
        TriggerOverlap_Off,    /*!< */
        TriggerOverlap_ReadOut,    /*!< */
        TriggerOverlap_PreviousFrame,    /*!< */
        NUM_TRIGGEROVERLAP
    };

    enum TriggerSelectorEnums    /*!< Selects the type of trigger to configure.*/
    {
        TriggerSelector_AcquisitionStart,    /*!< */
        TriggerSelector_FrameStart,    /*!< */
        TriggerSelector_FrameBurstStart,    /*!< */
        NUM_TRIGGERSELECTOR
    };

    enum ExposureAutoEnums    /*!< Sets the automatic exposure mode*/
    {
        ExposureAuto_Off,    /*!< 
        Exposure time is manually controlled using ExposureTime
      */
        ExposureAuto_Once,    /*!< 
        Exposure time is adapted once by the device. Once it has converged,
        it returns to the Off state.
      */
        ExposureAuto_Continuous,    /*!< 
        Exposure time is constantly adapted by the device to maximize the
        dynamic range.
      */
        NUM_EXPOSUREAUTO
    };

    enum EventSelectorEnums    /*!< Selects which Event to enable or disable.*/
    {
        EventSelector_Error,    /*!< */
        EventSelector_ExposureEnd,    /*!< */
        EventSelector_SerialPortReceive,    /*!< */
        NUM_EVENTSELECTOR
    };

    enum EventNotificationEnums    /*!< Enables/Disables the selected event.*/
    {
        EventNotification_On,    /*!< */
        EventNotification_Off,    /*!< */
        NUM_EVENTNOTIFICATION
    };

    enum LogicBlockSelectorEnums    /*!< Selects which LogicBlock to configure*/
    {
        LogicBlockSelector_LogicBlock0,    /*!< */
        LogicBlockSelector_LogicBlock1,    /*!< */
        NUM_LOGICBLOCKSELECTOR
    };

    enum LogicBlockLUTInputActivationEnums    /*!< Selects the activation mode of the Logic Input Source signal.*/
    {
        LogicBlockLUTInputActivation_LevelLow,    /*!< */
        LogicBlockLUTInputActivation_LevelHigh,    /*!< */
        LogicBlockLUTInputActivation_FallingEdge,    /*!< */
        LogicBlockLUTInputActivation_RisingEdge,    /*!< */
        LogicBlockLUTInputActivation_AnyEdge,    /*!< */
        NUM_LOGICBLOCKLUTINPUTACTIVATION
    };

    enum LogicBlockLUTInputSelectorEnums    /*!< Controls which LogicBlockLUT Input Source & Activation to access.*/
    {
        LogicBlockLUTInputSelector_Input0,    /*!< */
        LogicBlockLUTInputSelector_Input1,    /*!< */
        LogicBlockLUTInputSelector_Input2,    /*!< */
        LogicBlockLUTInputSelector_Input3,    /*!< */
        NUM_LOGICBLOCKLUTINPUTSELECTOR
    };

    enum LogicBlockLUTInputSourceEnums    /*!< Selects the source for the input into the Logic LUT.*/
    {
        LogicBlockLUTInputSource_Zero,    /*!< Zero*/
        LogicBlockLUTInputSource_Line0,    /*!< Line0*/
        LogicBlockLUTInputSource_Line1,    /*!< Line1*/
        LogicBlockLUTInputSource_Line2,    /*!< Line2*/
        LogicBlockLUTInputSource_Line3,    /*!< Line3*/
        LogicBlockLUTInputSource_UserOutput0,    /*!< UserOutput0*/
        LogicBlockLUTInputSource_UserOutput1,    /*!< UserOutput1*/
        LogicBlockLUTInputSource_UserOutput2,    /*!< UserOutput2*/
        LogicBlockLUTInputSource_UserOutput3,    /*!< UserOutput3*/
        LogicBlockLUTInputSource_Counter0Start,    /*!< Counter0Start*/
        LogicBlockLUTInputSource_Counter1Start,    /*!< Counter1Start*/
        LogicBlockLUTInputSource_Counter0End,    /*!< Counter0End*/
        LogicBlockLUTInputSource_Counter1End,    /*!< Counter1End*/
        LogicBlockLUTInputSource_LogicBlock0,    /*!< LogicBlock0*/
        LogicBlockLUTInputSource_LogicBlock1,    /*!< LogicBlock1*/
        LogicBlockLUTInputSource_ExposureStart,    /*!< ExposureStart*/
        LogicBlockLUTInputSource_ExposureEnd,    /*!< ExposureEnd*/
        LogicBlockLUTInputSource_FrameTriggerWait,    /*!< FrameTriggerWait*/
        LogicBlockLUTInputSource_AcquisitionActive,    /*!< AcquisitionActive*/
        NUM_LOGICBLOCKLUTINPUTSOURCE
    };

    enum LogicBlockLUTSelectorEnums    /*!< Selects which LogicBlock LUT to configure*/
    {
        LogicBlockLUTSelector_Value,    /*!< */
        LogicBlockLUTSelector_Enable,    /*!< */
        NUM_LOGICBLOCKLUTSELECTOR
    };

    enum ColorTransformationSelectorEnums    /*!< 
        Selects which Color Transformation module is controlled by the various Color Transformation features
      */
    {
        ColorTransformationSelector_RGBtoRGB,    /*!< */
        ColorTransformationSelector_RGBtoYUV,    /*!< */
        NUM_COLORTRANSFORMATIONSELECTOR
    };

    enum RgbTransformLightSourceEnums    /*!< 
      Used to select from a set of RGBtoRGB transform matricies calibrated for different light sources.
      Selecting a value also sets the white balance ratios 
      (BalanceRatioRed and BalanceRatioBlue), but those can be overwritten through manual or auto white balance.
    */
    {
        RgbTransformLightSource_General,    /*!< 
        Uses a matrix calibrated for a wide range of light sources.
      */
        RgbTransformLightSource_Tungsten2800K,    /*!< 
        Uses a matrix optimized for tungsten/incandescent light with color temperature 2800K.
      */
        RgbTransformLightSource_WarmFluorescent3000K,    /*!< 
        Uses a matrix optimized for a typical warm fluoresecent light with color temperature 3000K.
      */
        RgbTransformLightSource_CoolFluorescent4000K,    /*!< 
        Uses a matrix optimized for a typical cool fluoresecent light with color temperature 4000K.
      */
        RgbTransformLightSource_Daylight5000K,    /*!< 
        Uses a matrix optimized for noon Daylight with color temperature 5000K.
      */
        RgbTransformLightSource_Cloudy6500K,    /*!< 
        Uses a matrix optimized for a cloudy sky with color temperature 6500K.
      */
        RgbTransformLightSource_Shade8000K,    /*!< 
        Uses a matrix optimized for shade with color temperature 8000K.
      */
        RgbTransformLightSource_Custom,    /*!< 
        Uses a custom matrix set by the user through the 
        ColorTransformationValueSelector and ColorTransformationValue controls.
      */
        NUM_RGBTRANSFORMLIGHTSOURCE
    };

    enum ColorTransformationValueSelectorEnums    /*!< 
      Selects the Gain factor or Offset of the Transformation matrix to access in the selected Color Transformation module
    */
    {
        ColorTransformationValueSelector_Gain00,    /*!< */
        ColorTransformationValueSelector_Gain01,    /*!< */
        ColorTransformationValueSelector_Gain02,    /*!< */
        ColorTransformationValueSelector_Gain10,    /*!< */
        ColorTransformationValueSelector_Gain11,    /*!< */
        ColorTransformationValueSelector_Gain12,    /*!< */
        ColorTransformationValueSelector_Gain20,    /*!< */
        ColorTransformationValueSelector_Gain21,    /*!< */
        ColorTransformationValueSelector_Gain22,    /*!< */
        ColorTransformationValueSelector_Offset0,    /*!< */
        ColorTransformationValueSelector_Offset1,    /*!< */
        ColorTransformationValueSelector_Offset2,    /*!< */
        NUM_COLORTRANSFORMATIONVALUESELECTOR
    };

    enum DeviceRegistersEndiannessEnums    /*!< Endianess of the registers of the device.*/
    {
        DeviceRegistersEndianness_Little,    /*!< */
        DeviceRegistersEndianness_Big,    /*!< */
        NUM_DEVICEREGISTERSENDIANNESS
    };

    enum DeviceScanTypeEnums    /*!< Scan type of the sensor of the device.*/
    {
        DeviceScanType_Areascan,    /*!< */
        NUM_DEVICESCANTYPE
    };

    enum DeviceCharacterSetEnums    /*!< 
      Character set used by the strings of the device`s bootstrap registers.
    */
    {
        DeviceCharacterSet_UTF8,    /*!< */
        DeviceCharacterSet_ASCII,    /*!< */
        NUM_DEVICECHARACTERSET
    };

    enum DeviceTLTypeEnums    /*!< Transport Layer type of the device.*/
    {
        DeviceTLType_GigEVision,    /*!< */
        DeviceTLType_CameraLink,    /*!< */
        DeviceTLType_CameraLinkHS,    /*!< */
        DeviceTLType_CoaXPress,    /*!< */
        DeviceTLType_USB3Vision,    /*!< */
        DeviceTLType_Custom,    /*!< */
        NUM_DEVICETLTYPE
    };

    enum DevicePowerSupplySelectorEnums    /*!< 
      Selects the power supply source to control or read.
    */
    {
        DevicePowerSupplySelector_External,    /*!< */
        NUM_DEVICEPOWERSUPPLYSELECTOR
    };

    enum DeviceTemperatureSelectorEnums    /*!< 
      Selects the location within the device, where the temperature will be measured.
    */
    {
        DeviceTemperatureSelector_Sensor,    /*!< */
        NUM_DEVICETEMPERATURESELECTOR
    };

    enum DeviceIndicatorModeEnums    /*!< Controls the LED behaviour: Inactive (off), Active (current status), or Error Status (off unless an error occurs).*/
    {
        DeviceIndicatorMode_Inactive,    /*!< */
        DeviceIndicatorMode_Active,    /*!< */
        DeviceIndicatorMode_ErrorStatus,    /*!< */
        NUM_DEVICEINDICATORMODE
    };

    enum AutoExposureControlPriorityEnums    /*!< 
      Selects whether to adjust gain or exposure first. 
      When gain priority is selected, the camera fixes the gain to 0 dB, and the exposure is adjusted according to the target grey level. If the maximum exposure is reached before the target grey level is hit, the gain starts to change to meet the target. This mode is used to have the minimum noise.
	  When exposure priority is selected, the camera sets the exposure to a small value (default is 5 ms). The gain is adjusted according to the target grey level. If maximum gain is reached before the target grey level is hit, the exposure starts to change to meet the target. This mode is used to capture fast motion. 
    */
    {
        AutoExposureControlPriority_Gain,    /*!< */
        AutoExposureControlPriority_ExposureTime,    /*!< */
        NUM_AUTOEXPOSURECONTROLPRIORITY
    };

    enum AutoExposureMeteringModeEnums    /*!< 
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
    */
    {
        AutoExposureMeteringMode_Average,    /*!< */
        AutoExposureMeteringMode_Spot,    /*!< */
        AutoExposureMeteringMode_Partial,    /*!< */
        AutoExposureMeteringMode_CenterWeighted,    /*!< */
        AutoExposureMeteringMode_HistgramPeak,    /*!< */
        NUM_AUTOEXPOSUREMETERINGMODE
    };

    enum BalanceWhiteAutoProfileEnums    /*!< Selects the profile used by BalanceWhiteAuto.*/
    {
        BalanceWhiteAutoProfile_Indoor,    /*!< Indoor auto white balance Profile. Can be used to compensate for artificial lighting.*/
        BalanceWhiteAutoProfile_Outdoor,    /*!< Outdoor auto white balance profile. Designed for scenes with
        natural lighting.
      */
        NUM_BALANCEWHITEAUTOPROFILE
    };

    enum AutoAlgorithmSelectorEnums    /*!< 
      Selects which Auto Algorithm is controlled by the RoiEnable, OffsetX, 
      OffsetY, Width, Height features.
    */
    {
        AutoAlgorithmSelector_Awb,    /*!< Selects the Auto White Balance algorithm.*/
        AutoAlgorithmSelector_Ae,    /*!< Selects the Auto Exposure algorithm.*/
        NUM_AUTOALGORITHMSELECTOR
    };

    enum AutoExposureTargetGreyValueAutoEnums    /*!< 
      This indicates whether the target image grey level is automatically set by the camera or manually set by the user. Note that the target grey level is in the linear domain before gamma correction is applied.
    */
    {
        AutoExposureTargetGreyValueAuto_Off,    /*!< Target grey value is manually controlled*/
        AutoExposureTargetGreyValueAuto_Continuous,    /*!< Target grey value is constantly adapted by the device to maximize the dynamic range.*/
        NUM_AUTOEXPOSURETARGETGREYVALUEAUTO
    };

    enum AutoExposureLightingModeEnums    /*!< 
      Selects a lighting mode: Backlight, Frontlight or Normal (default).
      a. Backlight compensation: used when a strong light is coming from the back of the object.
      b. Frontlight compensation: used when a strong light is shining in the front of the object while the background is dark. 
      c. Normal lighting: used when the object is not under backlight or frontlight conditions. When normal lighting is selected, metering modes are available.
    */
    {
        AutoExposureLightingMode_AutoDetect,    /*!< */
        AutoExposureLightingMode_Backlight,    /*!< */
        AutoExposureLightingMode_Frontlight,    /*!< */
        AutoExposureLightingMode_Normal,    /*!< */
        NUM_AUTOEXPOSURELIGHTINGMODE
    };

    enum GevIEEE1588StatusEnums    /*!< Provides the status of the IEEE 1588 clock.*/
    {
        GevIEEE1588Status_Initializing,    /*!< Initializing*/
        GevIEEE1588Status_Faulty,    /*!< Faulty*/
        GevIEEE1588Status_Disabled,    /*!< Disabled*/
        GevIEEE1588Status_Listening,    /*!< Listening*/
        GevIEEE1588Status_PreMaster,    /*!< Pre Master*/
        GevIEEE1588Status_Master,    /*!< Master*/
        GevIEEE1588Status_Passive,    /*!< Passive*/
        GevIEEE1588Status_Uncalibrated,    /*!< Uncalibrated*/
        GevIEEE1588Status_Slave,    /*!< Slave*/
        NUM_GEVIEEE1588STATUS
    };

    enum GevIEEE1588ModeEnums    /*!< Provides the mode of the IEEE 1588 clock.*/
    {
        GevIEEE1588Mode_Auto,    /*!< Automatic*/
        GevIEEE1588Mode_SlaveOnly,    /*!< Slave Only*/
        NUM_GEVIEEE1588MODE
    };

    enum GevIEEE1588ClockAccuracyEnums    /*!< Indicates the expected accuracy of the device clock when it is the grandmaster, or in the event it becomes the grandmaster.*/
    {
        GevIEEE1588ClockAccuracy_Unknown,    /*!< Unknown Accuracy*/
        NUM_GEVIEEE1588CLOCKACCURACY
    };

    enum GevCCPEnums    /*!< Controls the device access privilege of an application.*/
    {
        GevCCP_OpenAccess,    /*!< */
        GevCCP_ExclusiveAccess,    /*!< */
        GevCCP_ControlAccess,    /*!< */
        NUM_GEVCCP
    };

    enum GevSupportedOptionSelectorEnums    /*!< Selects the GEV option to interrogate for existing support.*/
    {
        GevSupportedOptionSelector_UserDefinedName,    /*!< */
        GevSupportedOptionSelector_SerialNumber,    /*!< */
        GevSupportedOptionSelector_HeartbeatDisable,    /*!< */
        GevSupportedOptionSelector_LinkSpeed,    /*!< */
        GevSupportedOptionSelector_CCPApplicationSocket,    /*!< */
        GevSupportedOptionSelector_ManifestTable,    /*!< */
        GevSupportedOptionSelector_TestData,    /*!< */
        GevSupportedOptionSelector_DiscoveryAckDelay,    /*!< */
        GevSupportedOptionSelector_DiscoveryAckDelayWritable,    /*!< */
        GevSupportedOptionSelector_ExtendedStatusCodes,    /*!< */
        GevSupportedOptionSelector_Action,    /*!< */
        GevSupportedOptionSelector_PendingAck,    /*!< */
        GevSupportedOptionSelector_EventData,    /*!< */
        GevSupportedOptionSelector_Event,    /*!< */
        GevSupportedOptionSelector_PacketResend,    /*!< */
        GevSupportedOptionSelector_WriteMem,    /*!< */
        GevSupportedOptionSelector_CommandsConcatenation,    /*!< */
        GevSupportedOptionSelector_IPConfigurationLLA,    /*!< */
        GevSupportedOptionSelector_IPConfigurationDHCP,    /*!< */
        GevSupportedOptionSelector_IPConfigurationPersistentIP,    /*!< */
        GevSupportedOptionSelector_StreamChannelSourceSocket,    /*!< */
        GevSupportedOptionSelector_MessageChannelSourceSocket,    /*!< */
        NUM_GEVSUPPORTEDOPTIONSELECTOR
    };

    enum BlackLevelSelectorEnums    /*!< 
      Selects which black level to control.  Only All can be set by the user. Analog and Digital are read-only.
    */
    {
        BlackLevelSelector_All,    /*!< */
        BlackLevelSelector_Analog,    /*!< */
        BlackLevelSelector_Digital,    /*!< */
        NUM_BLACKLEVELSELECTOR
    };

    enum BalanceWhiteAutoEnums    /*!< 
      White Balance compensates for color shifts caused by different lighting conditions. It can be automatically or manually controlled. For manual control, set to Off. For automatic control, set to Once or Continuous.
    */
    {
        BalanceWhiteAuto_Off,    /*!< Sets operation mode to Off, which is manual control.*/
        BalanceWhiteAuto_Once,    /*!< Sets operation mode to once. Once runs for a number of iterations and then sets White Balance Auto to Off.*/
        BalanceWhiteAuto_Continuous,    /*!< Sets operation mode to continuous. Continuous automatically adjusts values if the colors are imbalanced.*/
        NUM_BALANCEWHITEAUTO
    };

    enum GainAutoEnums    /*!< 
      Sets the automatic gain mode. Set to Off for manual control. Set to Once for a single automatic adjustment then return to Off. Set to Continuous for constant adjustment. In automatic modes, the camera adjusts the gain to maximize the dynamic range.*/
    {
        GainAuto_Off,    /*!< Gain is manually controlled*/
        GainAuto_Once,    /*!< 
        Gain is adapted once by the device. Once it has converged, it returns to the Off state.
      */
        GainAuto_Continuous,    /*!< 
        Gain is constantly adapted by the device to maximize the dynamic range.
      */
        NUM_GAINAUTO
    };

    enum BalanceRatioSelectorEnums    /*!< 
      Selects a balance ratio to configure once a balance ratio control has 
      been selected.
    */
    {
        BalanceRatioSelector_Red,    /*!< 
        Selects the red balance ratio control for adjustment.  The red balance 
        ratio is relative to the green channel.
      */
        BalanceRatioSelector_Blue,    /*!< 
        Selects the blue balance ratio control for adjustment. The blue balance
        ratio is relative to the green channel.
      */
        NUM_BALANCERATIOSELECTOR
    };

    enum GainSelectorEnums    /*!< 
	Selects which gain to control. The All selection is a total amplification across all channels (or taps).
	*/
    {
        GainSelector_All,    /*!< */
        NUM_GAINSELECTOR
    };

    enum DefectCorrectionModeEnums    /*!< 
    	Controls the method used for replacing defective pixels.
    */
    {
        DefectCorrectionMode_Average,    /*!< Pixels are replaced with the average of their neighbours.  This is the normal mode of operation.*/
        DefectCorrectionMode_Highlight,    /*!< Pixels are replaced with the maximum pixel value (i.e., 255 for 8-bit images).  Can be used for debugging the table.*/
        DefectCorrectionMode_Zero,    /*!< Pixels are replaced by the value zero.  Can be used for testing the table.*/
        NUM_DEFECTCORRECTIONMODE
    };

    enum UserSetSelectorEnums    /*!< 
      Selects the feature User Set to load, save or configure.
    */
    {
        UserSetSelector_Default,    /*!< Factory default set.*/
        UserSetSelector_UserSet0,    /*!< User configurable set 0.*/
        UserSetSelector_UserSet1,    /*!< User configurable set 1.*/
        NUM_USERSETSELECTOR
    };

    enum UserSetDefaultEnums    /*!< 
      Selects the feature User Set to load and make active by default when the device is restarted.
    */
    {
        UserSetDefault_Default,    /*!< Factory default set.*/
        UserSetDefault_UserSet0,    /*!< User configurable set 0.*/
        UserSetDefault_UserSet1,    /*!< User configurable set 1.*/
        NUM_USERSETDEFAULT
    };

    enum SerialPortBaudRateEnums    /*!< This feature controls the baud rate used by the selected serial port.*/
    {
        SerialPortBaudRate_Baud300,    /*!< */
        SerialPortBaudRate_Baud600,    /*!< */
        SerialPortBaudRate_Baud1200,    /*!< */
        SerialPortBaudRate_Baud2400,    /*!< */
        SerialPortBaudRate_Baud4800,    /*!< */
        SerialPortBaudRate_Baud9600,    /*!< */
        SerialPortBaudRate_Baud14400,    /*!< */
        SerialPortBaudRate_Baud19200,    /*!< */
        SerialPortBaudRate_Baud38400,    /*!< */
        SerialPortBaudRate_Baud57600,    /*!< */
        SerialPortBaudRate_Baud115200,    /*!< */
        SerialPortBaudRate_Baud230400,    /*!< */
        SerialPortBaudRate_Baud460800,    /*!< */
        SerialPortBaudRate_Baud921600,    /*!< */
        NUM_SERIALPORTBAUDRATE
    };

    enum SerialPortParityEnums    /*!< This feature controls the parity used by the selected serial port.*/
    {
        SerialPortParity_None,    /*!< */
        SerialPortParity_Odd,    /*!< */
        SerialPortParity_Even,    /*!< */
        SerialPortParity_Mark,    /*!< */
        SerialPortParity_Space,    /*!< */
        NUM_SERIALPORTPARITY
    };

    enum SerialPortSelectorEnums    /*!< Selects which serial port of the device to control.*/
    {
        SerialPortSelector_SerialPort0,    /*!< */
        NUM_SERIALPORTSELECTOR
    };

    enum SerialPortStopBitsEnums    /*!< This feature controls the number of stop bits used by the selected serial port.*/
    {
        SerialPortStopBits_Bits1,    /*!< */
        SerialPortStopBits_Bits1AndAHalf,    /*!< */
        SerialPortStopBits_Bits2,    /*!< */
        NUM_SERIALPORTSTOPBITS
    };

    enum SerialPortSourceEnums    /*!< Specifies the physical input Line on which to receive serial data.*/
    {
        SerialPortSource_Line0,    /*!< */
        SerialPortSource_Line1,    /*!< */
        SerialPortSource_Line2,    /*!< */
        SerialPortSource_Line3,    /*!< */
        SerialPortSource_Off,    /*!< */
        NUM_SERIALPORTSOURCE
    };

    enum SequencerModeEnums    /*!< Controls whether or not a sequencer is active.*/
    {
        SequencerMode_Off,    /*!< */
        SequencerMode_On,    /*!< */
        NUM_SEQUENCERMODE
    };

    enum SequencerConfigurationValidEnums    /*!< 
      Display whether the current sequencer configuration is valid to run.
    */
    {
        SequencerConfigurationValid_No,    /*!< */
        SequencerConfigurationValid_Yes,    /*!< */
        NUM_SEQUENCERCONFIGURATIONVALID
    };

    enum SequencerSetValidEnums    /*!< 
      Displays whether the currently selected sequencer set's register contents 
      are valid to use.
    */
    {
        SequencerSetValid_No,    /*!< */
        SequencerSetValid_Yes,    /*!< */
        NUM_SEQUENCERSETVALID
    };

    enum SequencerTriggerActivationEnums    /*!< 
      Specifies the activation mode of the sequencer trigger.
    */
    {
        SequencerTriggerActivation_RisingEdge,    /*!< */
        SequencerTriggerActivation_FallingEdge,    /*!< */
        SequencerTriggerActivation_AnyEdge,    /*!< */
        SequencerTriggerActivation_LevelHigh,    /*!< */
        SequencerTriggerActivation_LevelLow,    /*!< */
        NUM_SEQUENCERTRIGGERACTIVATION
    };

    enum SequencerConfigurationModeEnums    /*!< 
      Controls whether or not a sequencer is in configuration mode.
    */
    {
        SequencerConfigurationMode_Off,    /*!< */
        SequencerConfigurationMode_On,    /*!< */
        NUM_SEQUENCERCONFIGURATIONMODE
    };

    enum SequencerTriggerSourceEnums    /*!< 
      Specifies the internal signal or physical input line to use as the 
      sequencer trigger source.
    */
    {
        SequencerTriggerSource_Off,    /*!< */
        SequencerTriggerSource_FrameStart,    /*!< */
        NUM_SEQUENCERTRIGGERSOURCE
    };

    enum TransferQueueModeEnums    /*!< Specifies the operation mode of the transfer queue.*/
    {
        TransferQueueMode_FirstInFirstOut,    /*!< Blocks first In are transferred Out first.*/
        NUM_TRANSFERQUEUEMODE
    };

    enum TransferOperationModeEnums    /*!< Selects the operation mode of the transfer. Continuous is similar to Basic/Automatic but you can start/stop the transfer while acquisition runs independently. Multi Block transmits a specified number of blocks and then stops.*/
    {
        TransferOperationMode_Continuous,    /*!< Continuous*/
        TransferOperationMode_MultiBlock,    /*!< Multi Block*/
        NUM_TRANSFEROPERATIONMODE
    };

    enum TransferControlModeEnums    /*!< Selects the control method for the transfers. Basic and Automatic start transmitting data as soon as there is enough data to fill a link layer packet. User Controlled allows you to directly control the transfer of blocks.*/
    {
        TransferControlMode_Basic,    /*!< Basic*/
        TransferControlMode_Automatic,    /*!< Automatic*/
        TransferControlMode_UserControlled,    /*!< User Controlled*/
        NUM_TRANSFERCONTROLMODE
    };

    enum ChunkGainSelectorEnums    /*!< Selects which gain to retrieve*/
    {
        ChunkGainSelector_All,    /*!< */
        ChunkGainSelector_Red,    /*!< */
        ChunkGainSelector_Green,    /*!< */
        ChunkGainSelector_Blue,    /*!< */
        NUM_CHUNKGAINSELECTOR
    };

    enum ChunkSelectorEnums    /*!< Selects which chunk data to enable or disable.*/
    {
        ChunkSelector_Image,    /*!< */
        ChunkSelector_CRC,    /*!< */
        ChunkSelector_FrameID,    /*!< */
        ChunkSelector_OffsetX,    /*!< */
        ChunkSelector_OffsetY,    /*!< */
        ChunkSelector_Width,    /*!< */
        ChunkSelector_Height,    /*!< */
        ChunkSelector_ExposureTime,    /*!< */
        ChunkSelector_Gain,    /*!< */
        ChunkSelector_BlackLevel,    /*!< */
        ChunkSelector_PixelFormat,    /*!< */
        ChunkSelector_Timestamp,    /*!< */
        ChunkSelector_SequencerSetActive,    /*!< */
        ChunkSelector_SerialData,    /*!< */
        ChunkSelector_ExposureEndLineStatusAll,    /*!< */
        NUM_CHUNKSELECTOR
    };

    enum ChunkBlackLevelSelectorEnums    /*!< Selects which black level to retrieve*/
    {
        ChunkBlackLevelSelector_All,    /*!< */
        NUM_CHUNKBLACKLEVELSELECTOR
    };

    enum ChunkPixelFormatEnums    /*!< Format of the pixel provided by the camera*/
    {
        ChunkPixelFormat_Mono8,    /*!< */
        ChunkPixelFormat_Mono12Packed,    /*!< */
        ChunkPixelFormat_Mono16,    /*!< */
        ChunkPixelFormat_RGB8Packed,    /*!< */
        ChunkPixelFormat_YUV422Packed,    /*!< */
        ChunkPixelFormat_BayerGR8,    /*!< */
        ChunkPixelFormat_BayerRG8,    /*!< */
        ChunkPixelFormat_BayerGB8,    /*!< */
        ChunkPixelFormat_BayerBG8,    /*!< */
        ChunkPixelFormat_YCbCr601_422_8_CbYCrY,    /*!< */
        NUM_CHUNKPIXELFORMAT
    };

    enum FileOperationStatusEnums    /*!< Represents the file operation execution status.*/
    {
        FileOperationStatus_Success,    /*!< File Operation was sucessful.*/
        FileOperationStatus_Failure,    /*!< File Operation failed.*/
        FileOperationStatus_Overflow,    /*!< An overflow occurred while executing the File Operation.*/
        NUM_FILEOPERATIONSTATUS
    };

    enum FileOpenModeEnums    /*!< 
      The mode of the file when it is opened. The file can be opened for reading, writting or both. This must be set before opening the file.
    */
    {
        FileOpenMode_Read,    /*!< */
        FileOpenMode_Write,    /*!< */
        FileOpenMode_ReadWrite,    /*!< */
        NUM_FILEOPENMODE
    };

    enum FileOperationSelectorEnums    /*!< 
      Sets operation to execute on the selected file when the execute command is given.
    */
    {
        FileOperationSelector_Open,    /*!< */
        FileOperationSelector_Close,    /*!< */
        FileOperationSelector_Read,    /*!< */
        FileOperationSelector_Write,    /*!< */
        FileOperationSelector_Delete,    /*!< */
        NUM_FILEOPERATIONSELECTOR
    };

    enum FileSelectorEnums    /*!< 
      Selects which file is being operated on. This must be set before performing any file operations.
	*/
    {
        FileSelector_UserSetDefault,    /*!< */
        FileSelector_UserSet0,    /*!< */
        FileSelector_UserSet1,    /*!< */
        FileSelector_UserFile1,    /*!< */
        FileSelector_SerialPort0,    /*!< */
        NUM_FILESELECTOR
    };

    enum BinningSelectorEnums    /*!< 
      Selects which binning engine is controlled by the BinningHorizontal and 
      BinningVertical features.
    */
    {
        BinningSelector_All,    /*!< 
        The total amount of binning to be performed on the captured sensor data.
      */
        BinningSelector_Sensor,    /*!< 
        The portion of binning to be performed on the sensor directly.
      */
        BinningSelector_ISP,    /*!< 
        The portion of binning to be performed by the image signal processing
        engine (ISP) outside of the sensor. Note: the ISP can be disabled.
      */
        NUM_BINNINGSELECTOR
    };

    enum TestPatternGeneratorSelectorEnums    /*!< 
      Selects which test pattern generator is controlled by the TestPattern feature.
    */
    {
        TestPatternGeneratorSelector_Sensor,    /*!< TestPattern feature controls the sensor`s test pattern generator.*/
        TestPatternGeneratorSelector_PipelineStart,    /*!< TestPattern feature controls the test pattern inserted at the start of the image pipeline.*/
        NUM_TESTPATTERNGENERATORSELECTOR
    };

    enum TestPatternEnums    /*!< 
      Selects the type of test pattern that is generated by the device as image source.
    */
    {
        TestPattern_Off,    /*!< Test pattern is disabled.*/
        TestPattern_Increment,    /*!< Pixel value increments by 1 for each pixel.*/
        TestPattern_SensorTestPattern,    /*!< A test pattern generated by the image sensor.  The pattern varies for different sensor models.*/
        NUM_TESTPATTERN
    };

    enum PixelColorFilterEnums    /*!< 
	Type of color filter that is applied to the image. Only applies to Bayer pixel formats. All others have no color filter.
	*/
    {
        PixelColorFilter_None,    /*!< No color filter.*/
        PixelColorFilter_BayerRG,    /*!< Bayer Red Green filter.*/
        PixelColorFilter_BayerGB,    /*!< Bayer Green Blue filter.*/
        PixelColorFilter_BayerGR,    /*!< Bayer Green Red filter.*/
        PixelColorFilter_BayerBG,    /*!< Bayer Blue Green filter.*/
        NUM_PIXELCOLORFILTER
    };

    enum AdcBitDepthEnums    /*!< 
      Selects which ADC bit depth to use. A higher ADC bit depth results in better image quality but slower maximum frame rate.
    */
    {
        AdcBitDepth_Bit8,    /*!< */
        AdcBitDepth_Bit10,    /*!< */
        AdcBitDepth_Bit12,    /*!< */
        AdcBitDepth_Bit14,    /*!< */
        NUM_ADCBITDEPTH
    };

    enum DecimationHorizontalModeEnums    /*!< 
      The mode used to reduce the horizontal resolution when DecimationHorizontal is used.
      The current implementation only supports a single decimation mode: Discard.  Average should be achieved via Binning.
    */
    {
        DecimationHorizontalMode_Discard,    /*!< The value of every Nth pixel is kept, others are discarded.*/
        NUM_DECIMATIONHORIZONTALMODE
    };

    enum BinningVerticalModeEnums    /*!< */
    {
        BinningVerticalMode_Sum,    /*!< 
        The response from the combined vertical cells is added, resulting
        in increased sensitivity (a brighter image).
      */
        BinningVerticalMode_Average,    /*!< 
        The response from the combined vertical cells is averaged,
        resulting in increased signal/noise ratio. Not all sensors support average binning.
      */
        NUM_BINNINGVERTICALMODE
    };

    enum PixelSizeEnums    /*!< 
	Total size in bits of a pixel of the image.
	*/
    {
        PixelSize_Bpp1,    /*!< 1 bit per pixel.*/
        PixelSize_Bpp2,    /*!< 2 bits per pixel.*/
        PixelSize_Bpp4,    /*!< 4 bits per pixel.*/
        PixelSize_Bpp8,    /*!< 8 bits per pixel.*/
        PixelSize_Bpp10,    /*!< 10 bits per pixel.*/
        PixelSize_Bpp12,    /*!< 12 bits per pixel.*/
        PixelSize_Bpp14,    /*!< 14 bits per pixel.*/
        PixelSize_Bpp16,    /*!< 16 bits per pixel.*/
        PixelSize_Bpp20,    /*!< 20 bits per pixel.*/
        PixelSize_Bpp24,    /*!< 24 bits per pixel.*/
        PixelSize_Bpp30,    /*!< 30 bits per pixel.*/
        PixelSize_Bpp32,    /*!< 32 bits per pixel.*/
        PixelSize_Bpp36,    /*!< 36 bits per pixel.*/
        PixelSize_Bpp48,    /*!< 48 bits per pixel.*/
        PixelSize_Bpp64,    /*!< 64 bits per pixel.*/
        PixelSize_Bpp96,    /*!< 96 bits per pixel.*/
        NUM_PIXELSIZE
    };

    enum DecimationSelectorEnums    /*!< Selects which decimation layer is controlled by the DecimationHorizontal and DecimationVertical features.*/
    {
        DecimationSelector_All,    /*!< The total amount of decimation to be performed on the captured image data.*/
        DecimationSelector_Sensor,    /*!< The portion of decimation to be performed on the sensor directly. Currently this is the only decimation layer available and hence is identical to the "All" layer.  All decimation modification should therefore be done via the "All" layer only.
      */
        NUM_DECIMATIONSELECTOR
    };

    enum ImageCompressionModeEnums    /*!< */
    {
        ImageCompressionMode_Off,    /*!< */
        ImageCompressionMode_Lossless,    /*!< */
        NUM_IMAGECOMPRESSIONMODE
    };

    enum BinningHorizontalModeEnums    /*!< */
    {
        BinningHorizontalMode_Sum,    /*!< 
        The response from the combined horizontal cells is added, 
        resulting in increased sensitivity (a brighter image).
      */
        BinningHorizontalMode_Average,    /*!< 
        The response from the combined horizontal cells is averaged,
        resulting in increased signal/noise ratio. Not all sensors support average binning.
      */
        NUM_BINNINGHORIZONTALMODE
    };

    enum PixelFormatEnums    /*!< 
	Format of the pixel provided by the camera.
	*/
    {
        PixelFormat_Mono8,    /*!< */
        PixelFormat_Mono16,    /*!< */
        PixelFormat_RGB8Packed,    /*!< */
        PixelFormat_BayerGR8,    /*!< */
        PixelFormat_BayerRG8,    /*!< */
        PixelFormat_BayerGB8,    /*!< */
        PixelFormat_BayerBG8,    /*!< */
        PixelFormat_BayerGR16,    /*!< */
        PixelFormat_BayerRG16,    /*!< */
        PixelFormat_BayerGB16,    /*!< */
        PixelFormat_BayerBG16,    /*!< */
        PixelFormat_Mono12Packed,    /*!< */
        PixelFormat_BayerGR12Packed,    /*!< */
        PixelFormat_BayerRG12Packed,    /*!< */
        PixelFormat_BayerGB12Packed,    /*!< */
        PixelFormat_BayerBG12Packed,    /*!< */
        PixelFormat_YUV411Packed,    /*!< */
        PixelFormat_YUV422Packed,    /*!< */
        PixelFormat_YUV444Packed,    /*!< */
        PixelFormat_Mono12p,    /*!< */
        PixelFormat_BayerGR12p,    /*!< */
        PixelFormat_BayerRG12p,    /*!< */
        PixelFormat_BayerGB12p,    /*!< */
        PixelFormat_BayerBG12p,    /*!< */
        PixelFormat_YCbCr8,    /*!< */
        PixelFormat_YCbCr422_8,    /*!< */
        PixelFormat_YCbCr411_8,    /*!< */
        PixelFormat_BGR8,    /*!< */
        PixelFormat_BGRa8,    /*!< */
        PixelFormat_Mono10Packed,    /*!< */
        PixelFormat_BayerGR10Packed,    /*!< */
        PixelFormat_BayerRG10Packed,    /*!< */
        PixelFormat_BayerGB10Packed,    /*!< */
        PixelFormat_BayerBG10Packed,    /*!< */
        PixelFormat_Mono10p,    /*!< */
        PixelFormat_BayerGR10p,    /*!< */
        PixelFormat_BayerRG10p,    /*!< */
        PixelFormat_BayerGB10p,    /*!< */
        PixelFormat_BayerBG10p,    /*!< */
        PixelFormat_Mono1p,    /*!< Monochrome 1-bit packed*/
        PixelFormat_Mono2p,    /*!< Monochrome 2-bit packed*/
        PixelFormat_Mono4p,    /*!< Monochrome 4-bit packed*/
        PixelFormat_Mono8s,    /*!< Monochrome 8-bit signed*/
        PixelFormat_Mono10,    /*!< Monochrome 10-bit unpacked*/
        PixelFormat_Mono12,    /*!< Monochrome 12-bit unpacked*/
        PixelFormat_Mono14,    /*!< Monochrome 14-bit unpacked*/
        PixelFormat_Mono16s,    /*!< Monochrome 16-bit signed*/
        PixelFormat_Mono32f,    /*!< Monochrome 32-bit float*/
        PixelFormat_BayerBG10,    /*!< Bayer Blue-Green 10-bit unpacked*/
        PixelFormat_BayerBG12,    /*!< Bayer Blue-Green 12-bit unpacked*/
        PixelFormat_BayerGB10,    /*!< Bayer Green-Blue 10-bit unpacked*/
        PixelFormat_BayerGB12,    /*!< Bayer Green-Blue 12-bit unpacked*/
        PixelFormat_BayerGR10,    /*!< Bayer Green-Red 10-bit unpacked*/
        PixelFormat_BayerGR12,    /*!< Bayer Green-Red 12-bit unpacked*/
        PixelFormat_BayerRG10,    /*!< Bayer Red-Green 10-bit unpacked*/
        PixelFormat_BayerRG12,    /*!< Bayer Red-Green 12-bit unpacked*/
        PixelFormat_RGBa8,    /*!< Red-Green-Blue-alpha 8-bit*/
        PixelFormat_RGBa10,    /*!< Red-Green-Blue-alpha 10-bit unpacked*/
        PixelFormat_RGBa10p,    /*!< Red-Green-Blue-alpha 10-bit packed*/
        PixelFormat_RGBa12,    /*!< Red-Green-Blue-alpha 12-bit unpacked*/
        PixelFormat_RGBa12p,    /*!< Red-Green-Blue-alpha 12-bit packed*/
        PixelFormat_RGBa14,    /*!< Red-Green-Blue-alpha 14-bit unpacked*/
        PixelFormat_RGBa16,    /*!< Red-Green-Blue-alpha 16-bit*/
        PixelFormat_RGB8,    /*!< Red-Green-Blue 8-bit*/
        PixelFormat_RGB8_Planar,    /*!< Red-Green-Blue 8-bit planar*/
        PixelFormat_RGB10,    /*!< Red-Green-Blue 10-bit unpacked*/
        PixelFormat_RGB10_Planar,    /*!< Red-Green-Blue 10-bit unpacked planar*/
        PixelFormat_RGB10p,    /*!< Red-Green-Blue 10-bit packed*/
        PixelFormat_RGB10p32,    /*!< Red-Green-Blue 10-bit packed into 32-bit*/
        PixelFormat_RGB12,    /*!< Red-Green-Blue 12-bit unpacked*/
        PixelFormat_RGB12_Planar,    /*!< Red-Green-Blue 12-bit unpacked planar*/
        PixelFormat_RGB12p,    /*!< Red-Green-Blue 12-bit packed  */
        PixelFormat_RGB14,    /*!< Red-Green-Blue 14-bit unpacked*/
        PixelFormat_RGB16,    /*!< Red-Green-Blue 16-bit  */
        PixelFormat_RGB16s,    /*!< Red-Green-Blue 16-bit signed*/
        PixelFormat_RGB32f,    /*!< Red-Green-Blue 32-bit float*/
        PixelFormat_RGB16_Planar,    /*!< Red-Green-Blue 16-bit planar*/
        PixelFormat_RGB565p,    /*!< Red-Green-Blue 5/6/5-bit packed*/
        PixelFormat_BGRa10,    /*!< Blue-Green-Red-alpha 10-bit unpacked*/
        PixelFormat_BGRa10p,    /*!< Blue-Green-Red-alpha 10-bit packed*/
        PixelFormat_BGRa12,    /*!< Blue-Green-Red-alpha 12-bit unpacked*/
        PixelFormat_BGRa12p,    /*!< Blue-Green-Red-alpha 12-bit packed*/
        PixelFormat_BGRa14,    /*!< Blue-Green-Red-alpha 14-bit unpacked*/
        PixelFormat_BGRa16,    /*!< Blue-Green-Red-alpha 16-bit*/
        PixelFormat_RGBa32f,    /*!< Red-Green-Blue-alpha 32-bit float*/
        PixelFormat_BGR10,    /*!< Blue-Green-Red 10-bit unpacked*/
        PixelFormat_BGR10p,    /*!< Blue-Green-Red 10-bit packed*/
        PixelFormat_BGR12,    /*!< Blue-Green-Red 12-bit unpacked*/
        PixelFormat_BGR12p,    /*!< Blue-Green-Red 12-bit packed*/
        PixelFormat_BGR14,    /*!< Blue-Green-Red 14-bit unpacked*/
        PixelFormat_BGR16,    /*!< Blue-Green-Red 16-bit*/
        PixelFormat_BGR565p,    /*!< Blue-Green-Red 5/6/5-bit packed*/
        PixelFormat_R8,    /*!< Red 8-bit*/
        PixelFormat_R10,    /*!< Red 10-bit*/
        PixelFormat_R12,    /*!< Red 12-bit*/
        PixelFormat_R16,    /*!< Red 16-bit*/
        PixelFormat_G8,    /*!< Green 8-bit*/
        PixelFormat_G10,    /*!< Green 10-bit*/
        PixelFormat_G12,    /*!< Green 12-bit*/
        PixelFormat_G16,    /*!< Green 16-bit*/
        PixelFormat_B8,    /*!< Blue 8-bit*/
        PixelFormat_B10,    /*!< Blue 10-bit*/
        PixelFormat_B12,    /*!< Blue 12-bit*/
        PixelFormat_B16,    /*!< Blue 16-bit*/
        PixelFormat_Coord3D_ABC8,    /*!< 3D coordinate A-B-C 8-bit*/
        PixelFormat_Coord3D_ABC8_Planar,    /*!< 3D coordinate A-B-C 8-bit planar*/
        PixelFormat_Coord3D_ABC10p,    /*!< 3D coordinate A-B-C 10-bit packed*/
        PixelFormat_Coord3D_ABC10p_Planar,    /*!< 3D coordinate A-B-C 10-bit packed planar*/
        PixelFormat_Coord3D_ABC12p,    /*!< 3D coordinate A-B-C 12-bit packed*/
        PixelFormat_Coord3D_ABC12p_Planar,    /*!< 3D coordinate A-B-C 12-bit packed planar*/
        PixelFormat_Coord3D_ABC16,    /*!< 3D coordinate A-B-C 16-bit*/
        PixelFormat_Coord3D_ABC16_Planar,    /*!< 3D coordinate A-B-C 16-bit planar*/
        PixelFormat_Coord3D_ABC32f,    /*!< 3D coordinate A-B-C 32-bit floating point*/
        PixelFormat_Coord3D_ABC32f_Planar,    /*!< 3D coordinate A-B-C 32-bit floating point planar*/
        PixelFormat_Coord3D_AC8,    /*!< 3D coordinate A-C 8-bit*/
        PixelFormat_Coord3D_AC8_Planar,    /*!< 3D coordinate A-C 8-bit planar*/
        PixelFormat_Coord3D_AC10p,    /*!< 3D coordinate A-C 10-bit packed*/
        PixelFormat_Coord3D_AC10p_Planar,    /*!< 3D coordinate A-C 10-bit packed planar*/
        PixelFormat_Coord3D_AC12p,    /*!< 3D coordinate A-C 12-bit packed*/
        PixelFormat_Coord3D_AC12p_Planar,    /*!< 3D coordinate A-C 12-bit packed planar*/
        PixelFormat_Coord3D_AC16,    /*!< 3D coordinate A-C 16-bit*/
        PixelFormat_Coord3D_AC16_Planar,    /*!< 3D coordinate A-C 16-bit planar*/
        PixelFormat_Coord3D_AC32f,    /*!< 3D coordinate A-C 32-bit floating point*/
        PixelFormat_Coord3D_AC32f_Planar,    /*!< 3D coordinate A-C 32-bit floating point planar*/
        PixelFormat_Coord3D_A8,    /*!< 3D coordinate A 8-bit*/
        PixelFormat_Coord3D_A10p,    /*!< 3D coordinate A 10-bit packed*/
        PixelFormat_Coord3D_A12p,    /*!< 3D coordinate A 12-bit packed*/
        PixelFormat_Coord3D_A16,    /*!< 3D coordinate A 16-bit*/
        PixelFormat_Coord3D_A32f,    /*!< 3D coordinate A 32-bit floating point*/
        PixelFormat_Coord3D_B8,    /*!< 3D coordinate B 8-bit*/
        PixelFormat_Coord3D_B10p,    /*!< 3D coordinate B 10-bit packed*/
        PixelFormat_Coord3D_B12p,    /*!< 3D coordinate B 12-bit packed*/
        PixelFormat_Coord3D_B16,    /*!< 3D coordinate B 16-bit*/
        PixelFormat_Coord3D_B32f,    /*!< 3D coordinate B 32-bit floating point*/
        PixelFormat_Coord3D_C8,    /*!< 3D coordinate C 8-bit*/
        PixelFormat_Coord3D_C10p,    /*!< 3D coordinate C 10-bit packed*/
        PixelFormat_Coord3D_C12p,    /*!< 3D coordinate C 12-bit packed*/
        PixelFormat_Coord3D_C16,    /*!< 3D coordinate C 16-bit*/
        PixelFormat_Coord3D_C32f,    /*!< 3D coordinate C 32-bit floating point*/
        PixelFormat_Confidence1,    /*!< Confidence 1-bit unpacked*/
        PixelFormat_Confidence1p,    /*!< Confidence 1-bit packed*/
        PixelFormat_Confidence8,    /*!< Confidence 8-bit*/
        PixelFormat_Confidence16,    /*!< Confidence 16-bit*/
        PixelFormat_Confidence32f,    /*!< Confidence 32-bit floating point*/
        PixelFormat_BiColorBGRG8,    /*!< Bi-color Blue/Green - Red/Green 8-bit*/
        PixelFormat_BiColorBGRG10,    /*!< Bi-color Blue/Green - Red/Green 10-bit unpacked*/
        PixelFormat_BiColorBGRG10p,    /*!< Bi-color Blue/Green - Red/Green 10-bit packed*/
        PixelFormat_BiColorBGRG12,    /*!< Bi-color Blue/Green - Red/Green 12-bit unpacked*/
        PixelFormat_BiColorBGRG12p,    /*!< Bi-color Blue/Green - Red/Green 12-bit packed*/
        PixelFormat_BiColorRGBG8,    /*!< Bi-color Red/Green - Blue/Green 8-bit*/
        PixelFormat_BiColorRGBG10,    /*!< Bi-color Red/Green - Blue/Green 10-bit unpacked*/
        PixelFormat_BiColorRGBG10p,    /*!< Bi-color Red/Green - Blue/Green 10-bit packed*/
        PixelFormat_BiColorRGBG12,    /*!< Bi-color Red/Green - Blue/Green 12-bit unpacked*/
        PixelFormat_BiColorRGBG12p,    /*!< Bi-color Red/Green - Blue/Green 12-bit packed*/
        PixelFormat_SCF1WBWG8,    /*!< Sparse Color Filter #1 White-Blue-White-Green 8-bit*/
        PixelFormat_SCF1WBWG10,    /*!< Sparse Color Filter #1 White-Blue-White-Green 10-bit unpacked*/
        PixelFormat_SCF1WBWG10p,    /*!< Sparse Color Filter #1 White-Blue-White-Green 10-bit packed*/
        PixelFormat_SCF1WBWG12,    /*!< Sparse Color Filter #1 White-Blue-White-Green 12-bit unpacked*/
        PixelFormat_SCF1WBWG12p,    /*!< Sparse Color Filter #1 White-Blue-White-Green 12-bit packed*/
        PixelFormat_SCF1WBWG14,    /*!< Sparse Color Filter #1 White-Blue-White-Green 14-bit unpacked*/
        PixelFormat_SCF1WBWG16,    /*!< Sparse Color Filter #1 White-Blue-White-Green 16-bit unpacked*/
        PixelFormat_SCF1WGWB8,    /*!< Sparse Color Filter #1 White-Green-White-Blue 8-bit*/
        PixelFormat_SCF1WGWB10,    /*!< Sparse Color Filter #1 White-Green-White-Blue 10-bit unpacked*/
        PixelFormat_SCF1WGWB10p,    /*!< Sparse Color Filter #1 White-Green-White-Blue 10-bit packed*/
        PixelFormat_SCF1WGWB12,    /*!< Sparse Color Filter #1 White-Green-White-Blue 12-bit unpacked*/
        PixelFormat_SCF1WGWB12p,    /*!< Sparse Color Filter #1 White-Green-White-Blue 12-bit packed*/
        PixelFormat_SCF1WGWB14,    /*!< Sparse Color Filter #1 White-Green-White-Blue 14-bit unpacked*/
        PixelFormat_SCF1WGWB16,    /*!< Sparse Color Filter #1 White-Green-White-Blue 16-bit*/
        PixelFormat_SCF1WGWR8,    /*!< Sparse Color Filter #1 White-Green-White-Red 8-bit*/
        PixelFormat_SCF1WGWR10,    /*!< Sparse Color Filter #1 White-Green-White-Red 10-bit unpacked*/
        PixelFormat_SCF1WGWR10p,    /*!< Sparse Color Filter #1 White-Green-White-Red 10-bit packed*/
        PixelFormat_SCF1WGWR12,    /*!< Sparse Color Filter #1 White-Green-White-Red 12-bit unpacked*/
        PixelFormat_SCF1WGWR12p,    /*!< Sparse Color Filter #1 White-Green-White-Red 12-bit packed*/
        PixelFormat_SCF1WGWR14,    /*!< Sparse Color Filter #1 White-Green-White-Red 14-bit unpacked*/
        PixelFormat_SCF1WGWR16,    /*!< Sparse Color Filter #1 White-Green-White-Red 16-bit*/
        PixelFormat_SCF1WRWG8,    /*!< Sparse Color Filter #1 White-Red-White-Green 8-bit*/
        PixelFormat_SCF1WRWG10,    /*!< Sparse Color Filter #1 White-Red-White-Green 10-bit unpacked*/
        PixelFormat_SCF1WRWG10p,    /*!< Sparse Color Filter #1 White-Red-White-Green 10-bit packed*/
        PixelFormat_SCF1WRWG12,    /*!< Sparse Color Filter #1 White-Red-White-Green 12-bit unpacked*/
        PixelFormat_SCF1WRWG12p,    /*!< Sparse Color Filter #1 White-Red-White-Green 12-bit packed*/
        PixelFormat_SCF1WRWG14,    /*!< Sparse Color Filter #1 White-Red-White-Green 14-bit unpacked*/
        PixelFormat_SCF1WRWG16,    /*!< Sparse Color Filter #1 White-Red-White-Green 16-bit*/
        PixelFormat_YCbCr8_CbYCr,    /*!< YCbCr 4:4:4 8-bit*/
        PixelFormat_YCbCr10_CbYCr,    /*!< YCbCr 4:4:4 10-bit unpacked*/
        PixelFormat_YCbCr10p_CbYCr,    /*!< YCbCr 4:4:4 10-bit packed*/
        PixelFormat_YCbCr12_CbYCr,    /*!< YCbCr 4:4:4 12-bit unpacked*/
        PixelFormat_YCbCr12p_CbYCr,    /*!< YCbCr 4:4:4 12-bit packed*/
        PixelFormat_YCbCr411_8_CbYYCrYY,    /*!< YCbCr 4:1:1 8-bit*/
        PixelFormat_YCbCr422_8_CbYCrY,    /*!< YCbCr 4:2:2 8-bit*/
        PixelFormat_YCbCr422_10,    /*!< YCbCr 4:2:2 10-bit unpacked*/
        PixelFormat_YCbCr422_10_CbYCrY,    /*!< YCbCr 4:2:2 10-bit unpacked*/
        PixelFormat_YCbCr422_10p,    /*!< YCbCr 4:2:2 10-bit packed*/
        PixelFormat_YCbCr422_10p_CbYCrY,    /*!< YCbCr 4:2:2 10-bit packed*/
        PixelFormat_YCbCr422_12,    /*!< YCbCr 4:2:2 12-bit unpacked*/
        PixelFormat_YCbCr422_12_CbYCrY,    /*!< YCbCr 4:2:2 12-bit unpacked*/
        PixelFormat_YCbCr422_12p,    /*!< YCbCr 4:2:2 12-bit packed*/
        PixelFormat_YCbCr422_12p_CbYCrY,    /*!< YCbCr 4:2:2 12-bit packed*/
        PixelFormat_YCbCr601_8_CbYCr,    /*!< YCbCr 4:4:4 8-bit BT.601*/
        PixelFormat_YCbCr601_10_CbYCr,    /*!< YCbCr 4:4:4 10-bit unpacked BT.601*/
        PixelFormat_YCbCr601_10p_CbYCr,    /*!< YCbCr 4:4:4 10-bit packed BT.601*/
        PixelFormat_YCbCr601_12_CbYCr,    /*!< YCbCr 4:4:4 12-bit unpacked BT.601*/
        PixelFormat_YCbCr601_12p_CbYCr,    /*!< YCbCr 4:4:4 12-bit packed BT.601*/
        PixelFormat_YCbCr601_411_8_CbYYCrYY,    /*!< YCbCr 4:1:1 8-bit BT.601*/
        PixelFormat_YCbCr601_422_8,    /*!< YCbCr 4:2:2 8-bit BT.601*/
        PixelFormat_YCbCr601_422_8_CbYCrY,    /*!< YCbCr 4:2:2 8-bit BT.601*/
        PixelFormat_YCbCr601_422_10,    /*!< YCbCr 4:2:2 10-bit unpacked BT.601*/
        PixelFormat_YCbCr601_422_10_CbYCrY,    /*!< YCbCr 4:2:2 10-bit unpacked BT.601*/
        PixelFormat_YCbCr601_422_10p,    /*!< YCbCr 4:2:2 10-bit packed BT.601*/
        PixelFormat_YCbCr601_422_10p_CbYCrY,    /*!< YCbCr 4:2:2 10-bit packed BT.601*/
        PixelFormat_YCbCr601_422_12,    /*!< YCbCr 4:2:2 12-bit unpacked BT.601*/
        PixelFormat_YCbCr601_422_12_CbYCrY,    /*!< YCbCr 4:2:2 12-bit unpacked BT.601*/
        PixelFormat_YCbCr601_422_12p,    /*!< YCbCr 4:2:2 12-bit packed BT.601*/
        PixelFormat_YCbCr601_422_12p_CbYCrY,    /*!< YCbCr 4:2:2 12-bit packed BT.601*/
        PixelFormat_YCbCr709_8_CbYCr,    /*!< YCbCr 4:4:4 8-bit BT.709*/
        PixelFormat_YCbCr709_10_CbYCr,    /*!< YCbCr 4:4:4 10-bit unpacked BT.709*/
        PixelFormat_YCbCr709_10p_CbYCr,    /*!< YCbCr 4:4:4 10-bit packed BT.709*/
        PixelFormat_YCbCr709_12_CbYCr,    /*!< YCbCr 4:4:4 12-bit unpacked BT.709*/
        PixelFormat_YCbCr709_12p_CbYCr,    /*!< YCbCr 4:4:4 12-bit packed BT.709*/
        PixelFormat_YCbCr709_411_8_CbYYCrYY,    /*!< YCbCr 4:1:1 8-bit BT.709*/
        PixelFormat_YCbCr709_422_8,    /*!< YCbCr 4:2:2 8-bit BT.709*/
        PixelFormat_YCbCr709_422_8_CbYCrY,    /*!< YCbCr 4:2:2 8-bit BT.709*/
        PixelFormat_YCbCr709_422_10,    /*!< YCbCr 4:2:2 10-bit unpacked BT.709*/
        PixelFormat_YCbCr709_422_10_CbYCrY,    /*!< YCbCr 4:2:2 10-bit unpacked BT.709*/
        PixelFormat_YCbCr709_422_10p,    /*!< YCbCr 4:2:2 10-bit packed BT.709*/
        PixelFormat_YCbCr709_422_10p_CbYCrY,    /*!< YCbCr 4:2:2 10-bit packed BT.709*/
        PixelFormat_YCbCr709_422_12,    /*!< YCbCr 4:2:2 12-bit unpacked BT.709*/
        PixelFormat_YCbCr709_422_12_CbYCrY,    /*!< YCbCr 4:2:2 12-bit unpacked BT.709*/
        PixelFormat_YCbCr709_422_12p,    /*!< YCbCr 4:2:2 12-bit packed BT.709*/
        PixelFormat_YCbCr709_422_12p_CbYCrY,    /*!< YCbCr 4:2:2 12-bit packed BT.709*/
        PixelFormat_YUV8_UYV,    /*!< YUV 4:4:4 8-bit*/
        PixelFormat_YUV411_8_UYYVYY,    /*!< YUV 4:1:1 8-bit*/
        PixelFormat_YUV422_8,    /*!< YUV 4:2:2 8-bit*/
        PixelFormat_YUV422_8_UYVY,    /*!< YUV 4:2:2 8-bit*/
        PixelFormat_Polarized8,    /*!< Monochrome Polarized 8-bit*/
        PixelFormat_Polarized10p,    /*!< Monochrome Polarized 10-bit packed*/
        PixelFormat_Polarized12p,    /*!< Monochrome Polarized 12-bit packed*/
        PixelFormat_Polarized16,    /*!< Monochrome Polarized 16-bit*/
        PixelFormat_BayerRGPolarized8,    /*!< Polarized Bayer Red Green filter 8-bit*/
        PixelFormat_BayerRGPolarized10p,    /*!< Polarized Bayer Red Green filter 10-bit packed*/
        PixelFormat_BayerRGPolarized12p,    /*!< Polarized Bayer Red Green filter 12-bit packed*/
        PixelFormat_BayerRGPolarized16,    /*!< Polarized Bayer Red Green filter 16-bit*/
        PixelFormat_LLCMono8,    /*!< Lossless Compression Monochrome 8-bit*/
        PixelFormat_LLCBayerRG8,    /*!< Lossless Compression Bayer Red Green filter 8-bit*/
        PixelFormat_JPEGMono8,    /*!< JPEG Monochrome 8-bit*/
        PixelFormat_JPEGColor8,    /*!< JPEG Color 8-bit*/
        PixelFormat_Raw16,    /*!< Raw 16 bit.*/
        PixelFormat_Raw8,    /*!< Raw bit.*/
        PixelFormat_R12_Jpeg,    /*!< Red 12-bit JPEG.*/
        PixelFormat_GR12_Jpeg,    /*!< Green Red 12-bit JPEG.*/
        PixelFormat_GB12_Jpeg,    /*!< Green Blue 12-bit JPEG.*/
        PixelFormat_B12_Jpeg,    /*!< Blue 12-bit packed JPEG.*/
        UNKNOWN_PIXELFORMAT,
        NUM_PIXELFORMAT
    };

    enum DecimationVerticalModeEnums    /*!< 
      The mode used to reduce the vertical resolution when DecimationVertical is used.
      The current implementation only supports a single decimation mode: Discard.  Average should be achieved via Binning.
    */
    {
        DecimationVerticalMode_Discard,    /*!< The value of every Nth pixel is kept, others are discarded.*/
        NUM_DECIMATIONVERTICALMODE
    };

    enum LineModeEnums    /*!< Controls if the physical Line is used to Input or Output a signal.*/
    {
        LineMode_Input,    /*!< */
        LineMode_Output,    /*!< */
        NUM_LINEMODE
    };

    enum LineSourceEnums    /*!< Selects which internal acquisition or I/O source signal to output on the selected line. LineMode must be Output.*/
    {
        LineSource_Off,    /*!< */
        LineSource_Line0,    /*!< */
        LineSource_Line1,    /*!< */
        LineSource_Line2,    /*!< */
        LineSource_Line3,    /*!< */
        LineSource_UserOutput0,    /*!< */
        LineSource_UserOutput1,    /*!< */
        LineSource_UserOutput2,    /*!< */
        LineSource_UserOutput3,    /*!< */
        LineSource_Counter0Active,    /*!< */
        LineSource_Counter1Active,    /*!< */
        LineSource_LogicBlock0,    /*!< */
        LineSource_LogicBlock1,    /*!< */
        LineSource_ExposureActive,    /*!< */
        LineSource_FrameTriggerWait,    /*!< */
        LineSource_SerialPort0,    /*!< */
        LineSource_PPSSignal,    /*!< */
        LineSource_AllPixel,    /*!< */
        LineSource_AnyPixel,    /*!< */
        NUM_LINESOURCE
    };

    enum LineInputFilterSelectorEnums    /*!< Selects the kind of input filter to configure: Deglitch or Debounce.*/
    {
        LineInputFilterSelector_Deglitch,    /*!< */
        LineInputFilterSelector_Debounce,    /*!< */
        NUM_LINEINPUTFILTERSELECTOR
    };

    enum UserOutputSelectorEnums    /*!< Selects which bit of the User Output register is set by UserOutputValue.*/
    {
        UserOutputSelector_UserOutput0,    /*!< */
        UserOutputSelector_UserOutput1,    /*!< */
        UserOutputSelector_UserOutput2,    /*!< */
        UserOutputSelector_UserOutput3,    /*!< */
        NUM_USEROUTPUTSELECTOR
    };

    enum LineFormatEnums    /*!< Displays the current electrical format of the selected physical input or output Line.*/
    {
        LineFormat_NoConnect,    /*!< */
        LineFormat_TriState,    /*!< */
        LineFormat_TTL,    /*!< */
        LineFormat_LVDS,    /*!< */
        LineFormat_RS422,    /*!< */
        LineFormat_OptoCoupled,    /*!< */
        LineFormat_OpenDrain,    /*!< */
        NUM_LINEFORMAT
    };

    enum LineSelectorEnums    /*!< Selects the physical line (or pin) of the external device connector to configure*/
    {
        LineSelector_Line0,    /*!< */
        LineSelector_Line1,    /*!< */
        LineSelector_Line2,    /*!< */
        LineSelector_Line3,    /*!< */
        NUM_LINESELECTOR
    };

    enum ExposureActiveModeEnums    /*!< Control sensor active exposure mode.*/
    {
        ExposureActiveMode_Line1,    /*!< */
        ExposureActiveMode_AnyPixels,    /*!< */
        ExposureActiveMode_AllPixels,    /*!< */
        NUM_EXPOSUREACTIVEMODE
    };

    enum CounterTriggerActivationEnums    /*!< Selects the activation mode of the trigger to start the Counter.*/
    {
        CounterTriggerActivation_LevelLow,    /*!< */
        CounterTriggerActivation_LevelHigh,    /*!< */
        CounterTriggerActivation_FallingEdge,    /*!< */
        CounterTriggerActivation_RisingEdge,    /*!< */
        CounterTriggerActivation_AnyEdge,    /*!< */
        NUM_COUNTERTRIGGERACTIVATION
    };

    enum CounterSelectorEnums    /*!< Selects which counter to configure*/
    {
        CounterSelector_Counter0,    /*!< */
        CounterSelector_Counter1,    /*!< */
        NUM_COUNTERSELECTOR
    };

    enum CounterStatusEnums    /*!< Returns the current status of the Counter.*/
    {
        CounterStatus_CounterIdle,    /*!< The counter is idle.*/
        CounterStatus_CounterTriggerWait,    /*!< The counter is waiting for a start trigger.*/
        CounterStatus_CounterActive,    /*!< The counter is counting for the specified duration.*/
        CounterStatus_CounterCompleted,    /*!< The counter reached the CounterDuration count.*/
        CounterStatus_CounterOverflow,    /*!< The counter reached its maximum possible count.*/
        NUM_COUNTERSTATUS
    };

    enum CounterTriggerSourceEnums    /*!< Selects the source of the trigger to start the counter*/
    {
        CounterTriggerSource_Off,    /*!< Off*/
        CounterTriggerSource_Line0,    /*!< Line0*/
        CounterTriggerSource_Line1,    /*!< Line1*/
        CounterTriggerSource_Line2,    /*!< Line2*/
        CounterTriggerSource_Line3,    /*!< Line3*/
        CounterTriggerSource_UserOutput0,    /*!< UserOutput0*/
        CounterTriggerSource_UserOutput1,    /*!< UserOutput1*/
        CounterTriggerSource_UserOutput2,    /*!< UserOutput2*/
        CounterTriggerSource_UserOutput3,    /*!< UserOutput3*/
        CounterTriggerSource_Counter0Start,    /*!< Counter0Start*/
        CounterTriggerSource_Counter1Start,    /*!< Counter1Start*/
        CounterTriggerSource_Counter0End,    /*!< Counter0End*/
        CounterTriggerSource_Counter1End,    /*!< Counter1End*/
        CounterTriggerSource_LogicBlock0,    /*!< LogicBlock0*/
        CounterTriggerSource_LogicBlock1,    /*!< LogicBlock1*/
        CounterTriggerSource_ExposureStart,    /*!< ExposureStart*/
        CounterTriggerSource_ExposureEnd,    /*!< ExposureEnd*/
        CounterTriggerSource_FrameTriggerWait,    /*!< FrameTriggerWait*/
        NUM_COUNTERTRIGGERSOURCE
    };

    enum CounterResetSourceEnums    /*!< Selects the signal that will be the source to reset the Counter.*/
    {
        CounterResetSource_Off,    /*!< Off*/
        CounterResetSource_Line0,    /*!< Line0*/
        CounterResetSource_Line1,    /*!< Line1*/
        CounterResetSource_Line2,    /*!< Line2*/
        CounterResetSource_Line3,    /*!< Line3*/
        CounterResetSource_UserOutput0,    /*!< UserOutput0*/
        CounterResetSource_UserOutput1,    /*!< UserOutput1*/
        CounterResetSource_UserOutput2,    /*!< UserOutput2*/
        CounterResetSource_UserOutput3,    /*!< UserOutput3*/
        CounterResetSource_Counter0Start,    /*!< Counter0Start*/
        CounterResetSource_Counter1Start,    /*!< Counter1Start*/
        CounterResetSource_Counter0End,    /*!< Counter0End*/
        CounterResetSource_Counter1End,    /*!< Counter1End*/
        CounterResetSource_LogicBlock0,    /*!< LogicBlock0*/
        CounterResetSource_LogicBlock1,    /*!< LogicBlock1*/
        CounterResetSource_ExposureStart,    /*!< ExposureStart*/
        CounterResetSource_ExposureEnd,    /*!< ExposureEnd*/
        CounterResetSource_FrameTriggerWait,    /*!< FrameTriggerWait*/
        NUM_COUNTERRESETSOURCE
    };

    enum CounterEventSourceEnums    /*!< Selects the event that will increment the counter*/
    {
        CounterEventSource_Off,    /*!< Off*/
        CounterEventSource_MHzTick,    /*!< MHzTick*/
        CounterEventSource_Line0,    /*!< Line0*/
        CounterEventSource_Line1,    /*!< Line1*/
        CounterEventSource_Line2,    /*!< Line2*/
        CounterEventSource_Line3,    /*!< Line3*/
        CounterEventSource_UserOutput0,    /*!< UserOutput0*/
        CounterEventSource_UserOutput1,    /*!< UserOutput1*/
        CounterEventSource_UserOutput2,    /*!< UserOutput2*/
        CounterEventSource_UserOutput3,    /*!< UserOutput3*/
        CounterEventSource_Counter0Start,    /*!< Counter0Start*/
        CounterEventSource_Counter1Start,    /*!< Counter1Start*/
        CounterEventSource_Counter0End,    /*!< Counter0End*/
        CounterEventSource_Counter1End,    /*!< Counter1End*/
        CounterEventSource_LogicBlock0,    /*!< LogicBlock0*/
        CounterEventSource_LogicBlock1,    /*!< LogicBlock1*/
        CounterEventSource_ExposureStart,    /*!< ExposureStart*/
        CounterEventSource_ExposureEnd,    /*!< ExposureEnd*/
        CounterEventSource_FrameTriggerWait,    /*!< FrameTriggerWait*/
        NUM_COUNTEREVENTSOURCE
    };

    enum CounterEventActivationEnums    /*!< Selects the activation mode of the event to increment the Counter.*/
    {
        CounterEventActivation_LevelLow,    /*!< */
        CounterEventActivation_LevelHigh,    /*!< */
        CounterEventActivation_FallingEdge,    /*!< */
        CounterEventActivation_RisingEdge,    /*!< */
        CounterEventActivation_AnyEdge,    /*!< */
        NUM_COUNTEREVENTACTIVATION
    };

    enum CounterResetActivationEnums    /*!< Selects the Activation mode of the Counter Reset Source signal.*/
    {
        CounterResetActivation_LevelLow,    /*!< */
        CounterResetActivation_LevelHigh,    /*!< */
        CounterResetActivation_FallingEdge,    /*!< */
        CounterResetActivation_RisingEdge,    /*!< */
        CounterResetActivation_AnyEdge,    /*!< */
        NUM_COUNTERRESETACTIVATION
    };

    enum DeviceTypeEnums    /*!< Returns the device type.*/
    {
        DeviceType_Transmitter,    /*!< Data stream transmitter device.*/
        DeviceType_Receiver,    /*!< Data stream receiver device.*/
        DeviceType_Transceiver,    /*!< Data stream receiver and transmitter device.*/
        DeviceType_Peripheral,    /*!< Controllable device (with no data stream handling).*/
        NUM_DEVICETYPE
    };

    enum DeviceConnectionStatusEnums    /*!< Indicates the status of the specified Connection.*/
    {
        DeviceConnectionStatus_Active,    /*!< Connection is in use.*/
        DeviceConnectionStatus_Inactive,    /*!< Connection is not in use.*/
        NUM_DEVICECONNECTIONSTATUS
    };

    enum DeviceLinkThroughputLimitModeEnums    /*!< Controls if the DeviceLinkThroughputLimit is active. When disabled, lower level TL specific features are expected to control the throughput. When enabled, DeviceLinkThroughputLimit controls the overall throughput.*/
    {
        DeviceLinkThroughputLimitMode_On,    /*!< Enables the DeviceLinkThroughputLimit feature.*/
        DeviceLinkThroughputLimitMode_Off,    /*!< Disables the DeviceLinkThroughputLimit feature.*/
        NUM_DEVICELINKTHROUGHPUTLIMITMODE
    };

    enum DeviceLinkHeartbeatModeEnums    /*!< Activate or deactivate the Link's heartbeat.*/
    {
        DeviceLinkHeartbeatMode_On,    /*!< Enables the Link heartbeat.*/
        DeviceLinkHeartbeatMode_Off,    /*!< Disables the Link heartbeat.*/
        NUM_DEVICELINKHEARTBEATMODE
    };

    enum DeviceStreamChannelTypeEnums    /*!< Reports the type of the stream channel.*/
    {
        DeviceStreamChannelType_Transmitter,    /*!< Data stream transmitter channel.*/
        DeviceStreamChannelType_Receiver,    /*!< Data stream receiver channel.*/
        NUM_DEVICESTREAMCHANNELTYPE
    };

    enum DeviceStreamChannelEndiannessEnums    /*!< Endianess of multi-byte pixel data for this stream.*/
    {
        DeviceStreamChannelEndianness_Big,    /*!< Stream channel data is big Endian.*/
        DeviceStreamChannelEndianness_Little,    /*!< Stream channel data is little Endian.*/
        NUM_DEVICESTREAMCHANNELENDIANNESS
    };

    enum DeviceClockSelectorEnums    /*!< Selects the clock frequency to access from the device.*/
    {
        DeviceClockSelector_Sensor,    /*!< Clock frequency of the image sensor of the camera.*/
        DeviceClockSelector_SensorDigitization,    /*!< Clock frequency of the camera A/D conversion stage.*/
        DeviceClockSelector_CameraLink,    /*!< Frequency of the Camera Link clock.*/
        NUM_DEVICECLOCKSELECTOR
    };

    enum DeviceSerialPortSelectorEnums    /*!< Selects which serial port of the device to control.*/
    {
        DeviceSerialPortSelector_CameraLink,    /*!< Serial port associated to the Camera link connection.*/
        NUM_DEVICESERIALPORTSELECTOR
    };

    enum DeviceSerialPortBaudRateEnums    /*!< This feature controls the baud rate used by the selected serial port.*/
    {
        DeviceSerialPortBaudRate_Baud9600,    /*!< Serial port speed of 9600 baud.*/
        DeviceSerialPortBaudRate_Baud19200,    /*!< Serial port speed of 19200 baud.*/
        DeviceSerialPortBaudRate_Baud38400,    /*!< Serial port speed of 38400 baud.*/
        DeviceSerialPortBaudRate_Baud57600,    /*!< Serial port speed of 57600 baud.*/
        DeviceSerialPortBaudRate_Baud115200,    /*!< Serial port speed of 115200 baud.*/
        DeviceSerialPortBaudRate_Baud230400,    /*!< Serial port speed of 230400 baud.*/
        DeviceSerialPortBaudRate_Baud460800,    /*!< Serial port speed of 460800 baud.*/
        DeviceSerialPortBaudRate_Baud921600,    /*!< Serial port speed of 921600 baud.*/
        NUM_DEVICESERIALPORTBAUDRATE
    };

    enum SensorTapsEnums    /*!< Number of taps of the camera sensor.*/
    {
        SensorTaps_One,    /*!< 1 tap.*/
        SensorTaps_Two,    /*!< 2 taps.*/
        SensorTaps_Three,    /*!< 3 taps.*/
        SensorTaps_Four,    /*!< 4 taps.*/
        SensorTaps_Eight,    /*!< 8 taps.*/
        SensorTaps_Ten,    /*!< 10 taps.*/
        NUM_SENSORTAPS
    };

    enum SensorDigitizationTapsEnums    /*!< Number of digitized samples outputted simultaneously by the camera A/D conversion stage.*/
    {
        SensorDigitizationTaps_One,    /*!< 1 tap.*/
        SensorDigitizationTaps_Two,    /*!< 2 taps.*/
        SensorDigitizationTaps_Three,    /*!< 3 taps.*/
        SensorDigitizationTaps_Four,    /*!< 4 taps.*/
        SensorDigitizationTaps_Eight,    /*!< 8 taps.*/
        SensorDigitizationTaps_Ten,    /*!< 10 taps.*/
        NUM_SENSORDIGITIZATIONTAPS
    };

    enum RegionSelectorEnums    /*!< Selects the Region of interest to control. The RegionSelector feature allows devices that are able to extract multiple regions out of an image, to configure the features of those individual regions independently.*/
    {
        RegionSelector_Region0,    /*!< Selected feature will control the region 0.*/
        RegionSelector_Region1,    /*!< Selected feature will control the region 1.*/
        RegionSelector_Region2,    /*!< Selected feature will control the region 2.*/
        RegionSelector_All,    /*!< Selected features will control all the regions at the same time.*/
        NUM_REGIONSELECTOR
    };

    enum RegionModeEnums    /*!< Controls if the selected Region of interest is active and streaming.*/
    {
        RegionMode_Off,    /*!< Disable the usage of the Region.*/
        RegionMode_On,    /*!< Enable the usage of the Region.*/
        NUM_REGIONMODE
    };

    enum RegionDestinationEnums    /*!< Control the destination of the selected region.*/
    {
        RegionDestination_Stream0,    /*!< The destination of the region is the data stream 0.*/
        RegionDestination_Stream1,    /*!< The destination of the region is the data stream 1.*/
        RegionDestination_Stream2,    /*!< The destination of the region is the data stream 2.*/
        NUM_REGIONDESTINATION
    };

    enum ImageComponentSelectorEnums    /*!< Selects a component to activate data streaming from.*/
    {
        ImageComponentSelector_Intensity,    /*!< The acquisition of intensity of the reflected light is controlled.*/
        ImageComponentSelector_Color,    /*!< The acquisition of color of the reflected light is controlled*/
        ImageComponentSelector_Infrared,    /*!< The acquisition of non-visible infrared light is controlled.*/
        ImageComponentSelector_Ultraviolet,    /*!< The acquisition of non-visible ultraviolet light is controlled.*/
        ImageComponentSelector_Range,    /*!< The acquisition of range (distance) data is controlled. The data produced may be only range (2.5D) or a point cloud 3D coordinates depending on the Scan3dControl.*/
        ImageComponentSelector_Disparity,    /*!< The acquisition of stereo camera disparity data is controlled. Disparity is a more specific range format approximately inversely proportional to distance. Disparity is typically given in pixel units.*/
        ImageComponentSelector_Confidence,    /*!< The acquisition of confidence map of the acquired image is controlled. Confidence data may be binary (0 - invalid) or an integer where 0 is invalid and increasing value is increased confidence in the data in the corresponding pixel. If floating point representation is used the confidence image is normalized to the range [0,1], for integer representation the maximum possible integer represents maximum confidence.*/
        ImageComponentSelector_Scatter,    /*!< The acquisition of data measuring how much light is scattered around the reflected light. In processing this is used as an additional intensity image, often together with the standard intensity.*/
        NUM_IMAGECOMPONENTSELECTOR
    };

    enum PixelFormatInfoSelectorEnums    /*!< Select the pixel format for which the information will be returned.*/
    {
        PixelFormatInfoSelector_Mono1p,    /*!< Monochrome 1-bit packed*/
        PixelFormatInfoSelector_Mono2p,    /*!< Monochrome 2-bit packed*/
        PixelFormatInfoSelector_Mono4p,    /*!< Monochrome 4-bit packed*/
        PixelFormatInfoSelector_Mono8,    /*!< Monochrome 8-bit*/
        PixelFormatInfoSelector_Mono8s,    /*!< Monochrome 8-bit signed*/
        PixelFormatInfoSelector_Mono10,    /*!< Monochrome 10-bit unpacked*/
        PixelFormatInfoSelector_Mono10p,    /*!< Monochrome 10-bit packed*/
        PixelFormatInfoSelector_Mono12,    /*!< Monochrome 12-bit unpacked*/
        PixelFormatInfoSelector_Mono12p,    /*!< Monochrome 12-bit packed*/
        PixelFormatInfoSelector_Mono14,    /*!< Monochrome 14-bit unpacked*/
        PixelFormatInfoSelector_Mono16,    /*!< Monochrome 16-bit*/
        PixelFormatInfoSelector_Mono16s,    /*!< Monochrome 16-bit signed*/
        PixelFormatInfoSelector_Mono32f,    /*!< Monochrome 32-bit float*/
        PixelFormatInfoSelector_BayerBG8,    /*!< Bayer Blue-Green 8-bit*/
        PixelFormatInfoSelector_BayerBG10,    /*!< Bayer Blue-Green 10-bit unpacked*/
        PixelFormatInfoSelector_BayerBG10p,    /*!< Bayer Blue-Green 10-bit packed*/
        PixelFormatInfoSelector_BayerBG12,    /*!< Bayer Blue-Green 12-bit unpacked*/
        PixelFormatInfoSelector_BayerBG12p,    /*!< Bayer Blue-Green 12-bit packed*/
        PixelFormatInfoSelector_BayerBG16,    /*!< Bayer Blue-Green 16-bit*/
        PixelFormatInfoSelector_BayerGB8,    /*!< Bayer Green-Blue 8-bit*/
        PixelFormatInfoSelector_BayerGB10,    /*!< Bayer Green-Blue 10-bit unpacked*/
        PixelFormatInfoSelector_BayerGB10p,    /*!< Bayer Green-Blue 10-bit packed*/
        PixelFormatInfoSelector_BayerGB12,    /*!< Bayer Green-Blue 12-bit unpacked*/
        PixelFormatInfoSelector_BayerGB12p,    /*!< Bayer Green-Blue 12-bit packed*/
        PixelFormatInfoSelector_BayerGB16,    /*!< Bayer Green-Blue 16-bit*/
        PixelFormatInfoSelector_BayerGR8,    /*!< Bayer Green-Red 8-bit*/
        PixelFormatInfoSelector_BayerGR10,    /*!< Bayer Green-Red 10-bit unpacked*/
        PixelFormatInfoSelector_BayerGR10p,    /*!< Bayer Green-Red 10-bit packed*/
        PixelFormatInfoSelector_BayerGR12,    /*!< Bayer Green-Red 12-bit unpacked*/
        PixelFormatInfoSelector_BayerGR12p,    /*!< Bayer Green-Red 12-bit packed*/
        PixelFormatInfoSelector_BayerGR16,    /*!< Bayer Green-Red 16-bit*/
        PixelFormatInfoSelector_BayerRG8,    /*!< Bayer Red-Green 8-bit*/
        PixelFormatInfoSelector_BayerRG10,    /*!< Bayer Red-Green 10-bit unpacked*/
        PixelFormatInfoSelector_BayerRG10p,    /*!< Bayer Red-Green 10-bit packed*/
        PixelFormatInfoSelector_BayerRG12,    /*!< Bayer Red-Green 12-bit unpacked*/
        PixelFormatInfoSelector_BayerRG12p,    /*!< Bayer Red-Green 12-bit packed*/
        PixelFormatInfoSelector_BayerRG16,    /*!< Bayer Red-Green 16-bit*/
        PixelFormatInfoSelector_RGBa8,    /*!< Red-Green-Blue-alpha 8-bit*/
        PixelFormatInfoSelector_RGBa10,    /*!< Red-Green-Blue-alpha 10-bit unpacked*/
        PixelFormatInfoSelector_RGBa10p,    /*!< Red-Green-Blue-alpha 10-bit packed*/
        PixelFormatInfoSelector_RGBa12,    /*!< Red-Green-Blue-alpha 12-bit unpacked*/
        PixelFormatInfoSelector_RGBa12p,    /*!< Red-Green-Blue-alpha 12-bit packed*/
        PixelFormatInfoSelector_RGBa14,    /*!< Red-Green-Blue-alpha 14-bit unpacked*/
        PixelFormatInfoSelector_RGBa16,    /*!< Red-Green-Blue-alpha 16-bit*/
        PixelFormatInfoSelector_RGB8,    /*!< Red-Green-Blue 8-bit*/
        PixelFormatInfoSelector_RGB8_Planar,    /*!< Red-Green-Blue 8-bit planar*/
        PixelFormatInfoSelector_RGB10,    /*!< Red-Green-Blue 10-bit unpacked*/
        PixelFormatInfoSelector_RGB10_Planar,    /*!< Red-Green-Blue 10-bit unpacked planar*/
        PixelFormatInfoSelector_RGB10p,    /*!< Red-Green-Blue 10-bit packed*/
        PixelFormatInfoSelector_RGB10p32,    /*!< Red-Green-Blue 10-bit packed into 32-bit*/
        PixelFormatInfoSelector_RGB12,    /*!< Red-Green-Blue 12-bit unpacked*/
        PixelFormatInfoSelector_RGB12_Planar,    /*!< Red-Green-Blue 12-bit unpacked planar*/
        PixelFormatInfoSelector_RGB12p,    /*!< Red-Green-Blue 12-bit packed  */
        PixelFormatInfoSelector_RGB14,    /*!< Red-Green-Blue 14-bit unpacked*/
        PixelFormatInfoSelector_RGB16,    /*!< Red-Green-Blue 16-bit  */
        PixelFormatInfoSelector_RGB16s,    /*!< Red-Green-Blue 16-bit signed*/
        PixelFormatInfoSelector_RGB32f,    /*!< Red-Green-Blue 32-bit float*/
        PixelFormatInfoSelector_RGB16_Planar,    /*!< Red-Green-Blue 16-bit planar*/
        PixelFormatInfoSelector_RGB565p,    /*!< Red-Green-Blue 5/6/5-bit packed*/
        PixelFormatInfoSelector_BGRa8,    /*!< Blue-Green-Red-alpha 8-bit*/
        PixelFormatInfoSelector_BGRa10,    /*!< Blue-Green-Red-alpha 10-bit unpacked*/
        PixelFormatInfoSelector_BGRa10p,    /*!< Blue-Green-Red-alpha 10-bit packed*/
        PixelFormatInfoSelector_BGRa12,    /*!< Blue-Green-Red-alpha 12-bit unpacked*/
        PixelFormatInfoSelector_BGRa12p,    /*!< Blue-Green-Red-alpha 12-bit packed*/
        PixelFormatInfoSelector_BGRa14,    /*!< Blue-Green-Red-alpha 14-bit unpacked*/
        PixelFormatInfoSelector_BGRa16,    /*!< Blue-Green-Red-alpha 16-bit*/
        PixelFormatInfoSelector_RGBa32f,    /*!< Red-Green-Blue-alpha 32-bit float*/
        PixelFormatInfoSelector_BGR8,    /*!< Blue-Green-Red 8-bit*/
        PixelFormatInfoSelector_BGR10,    /*!< Blue-Green-Red 10-bit unpacked*/
        PixelFormatInfoSelector_BGR10p,    /*!< Blue-Green-Red 10-bit packed*/
        PixelFormatInfoSelector_BGR12,    /*!< Blue-Green-Red 12-bit unpacked*/
        PixelFormatInfoSelector_BGR12p,    /*!< Blue-Green-Red 12-bit packed*/
        PixelFormatInfoSelector_BGR14,    /*!< Blue-Green-Red 14-bit unpacked*/
        PixelFormatInfoSelector_BGR16,    /*!< Blue-Green-Red 16-bit*/
        PixelFormatInfoSelector_BGR565p,    /*!< Blue-Green-Red 5/6/5-bit packed*/
        PixelFormatInfoSelector_R8,    /*!< Red 8-bit*/
        PixelFormatInfoSelector_R10,    /*!< Red 10-bit*/
        PixelFormatInfoSelector_R12,    /*!< Red 12-bit*/
        PixelFormatInfoSelector_R16,    /*!< Red 16-bit*/
        PixelFormatInfoSelector_G8,    /*!< Green 8-bit*/
        PixelFormatInfoSelector_G10,    /*!< Green 10-bit*/
        PixelFormatInfoSelector_G12,    /*!< Green 12-bit*/
        PixelFormatInfoSelector_G16,    /*!< Green 16-bit*/
        PixelFormatInfoSelector_B8,    /*!< Blue 8-bit*/
        PixelFormatInfoSelector_B10,    /*!< Blue 10-bit*/
        PixelFormatInfoSelector_B12,    /*!< Blue 12-bit*/
        PixelFormatInfoSelector_B16,    /*!< Blue 16-bit*/
        PixelFormatInfoSelector_Coord3D_ABC8,    /*!< 3D coordinate A-B-C 8-bit*/
        PixelFormatInfoSelector_Coord3D_ABC8_Planar,    /*!< 3D coordinate A-B-C 8-bit planar*/
        PixelFormatInfoSelector_Coord3D_ABC10p,    /*!< 3D coordinate A-B-C 10-bit packed*/
        PixelFormatInfoSelector_Coord3D_ABC10p_Planar,    /*!< 3D coordinate A-B-C 10-bit packed planar*/
        PixelFormatInfoSelector_Coord3D_ABC12p,    /*!< 3D coordinate A-B-C 12-bit packed*/
        PixelFormatInfoSelector_Coord3D_ABC12p_Planar,    /*!< 3D coordinate A-B-C 12-bit packed planar*/
        PixelFormatInfoSelector_Coord3D_ABC16,    /*!< 3D coordinate A-B-C 16-bit*/
        PixelFormatInfoSelector_Coord3D_ABC16_Planar,    /*!< 3D coordinate A-B-C 16-bit planar*/
        PixelFormatInfoSelector_Coord3D_ABC32f,    /*!< 3D coordinate A-B-C 32-bit floating point*/
        PixelFormatInfoSelector_Coord3D_ABC32f_Planar,    /*!< 3D coordinate A-B-C 32-bit floating point planar*/
        PixelFormatInfoSelector_Coord3D_AC8,    /*!< 3D coordinate A-C 8-bit*/
        PixelFormatInfoSelector_Coord3D_AC8_Planar,    /*!< 3D coordinate A-C 8-bit planar*/
        PixelFormatInfoSelector_Coord3D_AC10p,    /*!< 3D coordinate A-C 10-bit packed*/
        PixelFormatInfoSelector_Coord3D_AC10p_Planar,    /*!< 3D coordinate A-C 10-bit packed planar*/
        PixelFormatInfoSelector_Coord3D_AC12p,    /*!< 3D coordinate A-C 12-bit packed*/
        PixelFormatInfoSelector_Coord3D_AC12p_Planar,    /*!< 3D coordinate A-C 12-bit packed planar*/
        PixelFormatInfoSelector_Coord3D_AC16,    /*!< 3D coordinate A-C 16-bit*/
        PixelFormatInfoSelector_Coord3D_AC16_Planar,    /*!< 3D coordinate A-C 16-bit planar*/
        PixelFormatInfoSelector_Coord3D_AC32f,    /*!< 3D coordinate A-C 32-bit floating point*/
        PixelFormatInfoSelector_Coord3D_AC32f_Planar,    /*!< 3D coordinate A-C 32-bit floating point planar*/
        PixelFormatInfoSelector_Coord3D_A8,    /*!< 3D coordinate A 8-bit*/
        PixelFormatInfoSelector_Coord3D_A10p,    /*!< 3D coordinate A 10-bit packed*/
        PixelFormatInfoSelector_Coord3D_A12p,    /*!< 3D coordinate A 12-bit packed*/
        PixelFormatInfoSelector_Coord3D_A16,    /*!< 3D coordinate A 16-bit*/
        PixelFormatInfoSelector_Coord3D_A32f,    /*!< 3D coordinate A 32-bit floating point*/
        PixelFormatInfoSelector_Coord3D_B8,    /*!< 3D coordinate B 8-bit*/
        PixelFormatInfoSelector_Coord3D_B10p,    /*!< 3D coordinate B 10-bit packed*/
        PixelFormatInfoSelector_Coord3D_B12p,    /*!< 3D coordinate B 12-bit packed*/
        PixelFormatInfoSelector_Coord3D_B16,    /*!< 3D coordinate B 16-bit*/
        PixelFormatInfoSelector_Coord3D_B32f,    /*!< 3D coordinate B 32-bit floating point*/
        PixelFormatInfoSelector_Coord3D_C8,    /*!< 3D coordinate C 8-bit*/
        PixelFormatInfoSelector_Coord3D_C10p,    /*!< 3D coordinate C 10-bit packed*/
        PixelFormatInfoSelector_Coord3D_C12p,    /*!< 3D coordinate C 12-bit packed*/
        PixelFormatInfoSelector_Coord3D_C16,    /*!< 3D coordinate C 16-bit*/
        PixelFormatInfoSelector_Coord3D_C32f,    /*!< 3D coordinate C 32-bit floating point*/
        PixelFormatInfoSelector_Confidence1,    /*!< Confidence 1-bit unpacked*/
        PixelFormatInfoSelector_Confidence1p,    /*!< Confidence 1-bit packed*/
        PixelFormatInfoSelector_Confidence8,    /*!< Confidence 8-bit*/
        PixelFormatInfoSelector_Confidence16,    /*!< Confidence 16-bit*/
        PixelFormatInfoSelector_Confidence32f,    /*!< Confidence 32-bit floating point*/
        PixelFormatInfoSelector_BiColorBGRG8,    /*!< Bi-color Blue/Green - Red/Green 8-bit*/
        PixelFormatInfoSelector_BiColorBGRG10,    /*!< Bi-color Blue/Green - Red/Green 10-bit unpacked*/
        PixelFormatInfoSelector_BiColorBGRG10p,    /*!< Bi-color Blue/Green - Red/Green 10-bit packed*/
        PixelFormatInfoSelector_BiColorBGRG12,    /*!< Bi-color Blue/Green - Red/Green 12-bit unpacked*/
        PixelFormatInfoSelector_BiColorBGRG12p,    /*!< Bi-color Blue/Green - Red/Green 12-bit packed*/
        PixelFormatInfoSelector_BiColorRGBG8,    /*!< Bi-color Red/Green - Blue/Green 8-bit*/
        PixelFormatInfoSelector_BiColorRGBG10,    /*!< Bi-color Red/Green - Blue/Green 10-bit unpacked*/
        PixelFormatInfoSelector_BiColorRGBG10p,    /*!< Bi-color Red/Green - Blue/Green 10-bit packed*/
        PixelFormatInfoSelector_BiColorRGBG12,    /*!< Bi-color Red/Green - Blue/Green 12-bit unpacked*/
        PixelFormatInfoSelector_BiColorRGBG12p,    /*!< Bi-color Red/Green - Blue/Green 12-bit packed*/
        PixelFormatInfoSelector_SCF1WBWG8,    /*!< Sparse Color Filter #1 White-Blue-White-Green 8-bit*/
        PixelFormatInfoSelector_SCF1WBWG10,    /*!< Sparse Color Filter #1 White-Blue-White-Green 10-bit unpacked*/
        PixelFormatInfoSelector_SCF1WBWG10p,    /*!< Sparse Color Filter #1 White-Blue-White-Green 10-bit packed*/
        PixelFormatInfoSelector_SCF1WBWG12,    /*!< Sparse Color Filter #1 White-Blue-White-Green 12-bit unpacked*/
        PixelFormatInfoSelector_SCF1WBWG12p,    /*!< Sparse Color Filter #1 White-Blue-White-Green 12-bit packed*/
        PixelFormatInfoSelector_SCF1WBWG14,    /*!< Sparse Color Filter #1 White-Blue-White-Green 14-bit unpacked*/
        PixelFormatInfoSelector_SCF1WBWG16,    /*!< Sparse Color Filter #1 White-Blue-White-Green 16-bit unpacked*/
        PixelFormatInfoSelector_SCF1WGWB8,    /*!< Sparse Color Filter #1 White-Green-White-Blue 8-bit*/
        PixelFormatInfoSelector_SCF1WGWB10,    /*!< Sparse Color Filter #1 White-Green-White-Blue 10-bit unpacked*/
        PixelFormatInfoSelector_SCF1WGWB10p,    /*!< Sparse Color Filter #1 White-Green-White-Blue 10-bit packed*/
        PixelFormatInfoSelector_SCF1WGWB12,    /*!< Sparse Color Filter #1 White-Green-White-Blue 12-bit unpacked*/
        PixelFormatInfoSelector_SCF1WGWB12p,    /*!< Sparse Color Filter #1 White-Green-White-Blue 12-bit packed*/
        PixelFormatInfoSelector_SCF1WGWB14,    /*!< Sparse Color Filter #1 White-Green-White-Blue 14-bit unpacked*/
        PixelFormatInfoSelector_SCF1WGWB16,    /*!< Sparse Color Filter #1 White-Green-White-Blue 16-bit*/
        PixelFormatInfoSelector_SCF1WGWR8,    /*!< Sparse Color Filter #1 White-Green-White-Red 8-bit*/
        PixelFormatInfoSelector_SCF1WGWR10,    /*!< Sparse Color Filter #1 White-Green-White-Red 10-bit unpacked*/
        PixelFormatInfoSelector_SCF1WGWR10p,    /*!< Sparse Color Filter #1 White-Green-White-Red 10-bit packed*/
        PixelFormatInfoSelector_SCF1WGWR12,    /*!< Sparse Color Filter #1 White-Green-White-Red 12-bit unpacked*/
        PixelFormatInfoSelector_SCF1WGWR12p,    /*!< Sparse Color Filter #1 White-Green-White-Red 12-bit packed*/
        PixelFormatInfoSelector_SCF1WGWR14,    /*!< Sparse Color Filter #1 White-Green-White-Red 14-bit unpacked*/
        PixelFormatInfoSelector_SCF1WGWR16,    /*!< Sparse Color Filter #1 White-Green-White-Red 16-bit*/
        PixelFormatInfoSelector_SCF1WRWG8,    /*!< Sparse Color Filter #1 White-Red-White-Green 8-bit*/
        PixelFormatInfoSelector_SCF1WRWG10,    /*!< Sparse Color Filter #1 White-Red-White-Green 10-bit unpacked*/
        PixelFormatInfoSelector_SCF1WRWG10p,    /*!< Sparse Color Filter #1 White-Red-White-Green 10-bit packed*/
        PixelFormatInfoSelector_SCF1WRWG12,    /*!< Sparse Color Filter #1 White-Red-White-Green 12-bit unpacked*/
        PixelFormatInfoSelector_SCF1WRWG12p,    /*!< Sparse Color Filter #1 White-Red-White-Green 12-bit packed*/
        PixelFormatInfoSelector_SCF1WRWG14,    /*!< Sparse Color Filter #1 White-Red-White-Green 14-bit unpacked*/
        PixelFormatInfoSelector_SCF1WRWG16,    /*!< Sparse Color Filter #1 White-Red-White-Green 16-bit*/
        PixelFormatInfoSelector_YCbCr8,    /*!< YCbCr 4:4:4 8-bit*/
        PixelFormatInfoSelector_YCbCr8_CbYCr,    /*!< YCbCr 4:4:4 8-bit*/
        PixelFormatInfoSelector_YCbCr10_CbYCr,    /*!< YCbCr 4:4:4 10-bit unpacked*/
        PixelFormatInfoSelector_YCbCr10p_CbYCr,    /*!< YCbCr 4:4:4 10-bit packed*/
        PixelFormatInfoSelector_YCbCr12_CbYCr,    /*!< YCbCr 4:4:4 12-bit unpacked*/
        PixelFormatInfoSelector_YCbCr12p_CbYCr,    /*!< YCbCr 4:4:4 12-bit packed*/
        PixelFormatInfoSelector_YCbCr411_8,    /*!< YCbCr 4:1:1 8-bit*/
        PixelFormatInfoSelector_YCbCr411_8_CbYYCrYY,    /*!< YCbCr 4:1:1 8-bit*/
        PixelFormatInfoSelector_YCbCr422_8,    /*!< YCbCr 4:2:2 8-bit*/
        PixelFormatInfoSelector_YCbCr422_8_CbYCrY,    /*!< YCbCr 4:2:2 8-bit*/
        PixelFormatInfoSelector_YCbCr422_10,    /*!< YCbCr 4:2:2 10-bit unpacked*/
        PixelFormatInfoSelector_YCbCr422_10_CbYCrY,    /*!< YCbCr 4:2:2 10-bit unpacked*/
        PixelFormatInfoSelector_YCbCr422_10p,    /*!< YCbCr 4:2:2 10-bit packed*/
        PixelFormatInfoSelector_YCbCr422_10p_CbYCrY,    /*!< YCbCr 4:2:2 10-bit packed*/
        PixelFormatInfoSelector_YCbCr422_12,    /*!< YCbCr 4:2:2 12-bit unpacked*/
        PixelFormatInfoSelector_YCbCr422_12_CbYCrY,    /*!< YCbCr 4:2:2 12-bit unpacked*/
        PixelFormatInfoSelector_YCbCr422_12p,    /*!< YCbCr 4:2:2 12-bit packed*/
        PixelFormatInfoSelector_YCbCr422_12p_CbYCrY,    /*!< YCbCr 4:2:2 12-bit packed*/
        PixelFormatInfoSelector_YCbCr601_8_CbYCr,    /*!< YCbCr 4:4:4 8-bit BT.601*/
        PixelFormatInfoSelector_YCbCr601_10_CbYCr,    /*!< YCbCr 4:4:4 10-bit unpacked BT.601*/
        PixelFormatInfoSelector_YCbCr601_10p_CbYCr,    /*!< YCbCr 4:4:4 10-bit packed BT.601*/
        PixelFormatInfoSelector_YCbCr601_12_CbYCr,    /*!< YCbCr 4:4:4 12-bit unpacked BT.601*/
        PixelFormatInfoSelector_YCbCr601_12p_CbYCr,    /*!< YCbCr 4:4:4 12-bit packed BT.601*/
        PixelFormatInfoSelector_YCbCr601_411_8_CbYYCrYY,    /*!< YCbCr 4:1:1 8-bit BT.601*/
        PixelFormatInfoSelector_YCbCr601_422_8,    /*!< YCbCr 4:2:2 8-bit BT.601*/
        PixelFormatInfoSelector_YCbCr601_422_8_CbYCrY,    /*!< YCbCr 4:2:2 8-bit BT.601*/
        PixelFormatInfoSelector_YCbCr601_422_10,    /*!< YCbCr 4:2:2 10-bit unpacked BT.601*/
        PixelFormatInfoSelector_YCbCr601_422_10_CbYCrY,    /*!< YCbCr 4:2:2 10-bit unpacked BT.601*/
        PixelFormatInfoSelector_YCbCr601_422_10p,    /*!< YCbCr 4:2:2 10-bit packed BT.601*/
        PixelFormatInfoSelector_YCbCr601_422_10p_CbYCrY,    /*!< YCbCr 4:2:2 10-bit packed BT.601*/
        PixelFormatInfoSelector_YCbCr601_422_12,    /*!< YCbCr 4:2:2 12-bit unpacked BT.601*/
        PixelFormatInfoSelector_YCbCr601_422_12_CbYCrY,    /*!< YCbCr 4:2:2 12-bit unpacked BT.601*/
        PixelFormatInfoSelector_YCbCr601_422_12p,    /*!< YCbCr 4:2:2 12-bit packed BT.601*/
        PixelFormatInfoSelector_YCbCr601_422_12p_CbYCrY,    /*!< YCbCr 4:2:2 12-bit packed BT.601*/
        PixelFormatInfoSelector_YCbCr709_8_CbYCr,    /*!< YCbCr 4:4:4 8-bit BT.709*/
        PixelFormatInfoSelector_YCbCr709_10_CbYCr,    /*!< YCbCr 4:4:4 10-bit unpacked BT.709*/
        PixelFormatInfoSelector_YCbCr709_10p_CbYCr,    /*!< YCbCr 4:4:4 10-bit packed BT.709*/
        PixelFormatInfoSelector_YCbCr709_12_CbYCr,    /*!< YCbCr 4:4:4 12-bit unpacked BT.709*/
        PixelFormatInfoSelector_YCbCr709_12p_CbYCr,    /*!< YCbCr 4:4:4 12-bit packed BT.709*/
        PixelFormatInfoSelector_YCbCr709_411_8_CbYYCrYY,    /*!< YCbCr 4:1:1 8-bit BT.709*/
        PixelFormatInfoSelector_YCbCr709_422_8,    /*!< YCbCr 4:2:2 8-bit BT.709*/
        PixelFormatInfoSelector_YCbCr709_422_8_CbYCrY,    /*!< YCbCr 4:2:2 8-bit BT.709*/
        PixelFormatInfoSelector_YCbCr709_422_10,    /*!< YCbCr 4:2:2 10-bit unpacked BT.709*/
        PixelFormatInfoSelector_YCbCr709_422_10_CbYCrY,    /*!< YCbCr 4:2:2 10-bit unpacked BT.709*/
        PixelFormatInfoSelector_YCbCr709_422_10p,    /*!< YCbCr 4:2:2 10-bit packed BT.709*/
        PixelFormatInfoSelector_YCbCr709_422_10p_CbYCrY,    /*!< YCbCr 4:2:2 10-bit packed BT.709*/
        PixelFormatInfoSelector_YCbCr709_422_12,    /*!< YCbCr 4:2:2 12-bit unpacked BT.709*/
        PixelFormatInfoSelector_YCbCr709_422_12_CbYCrY,    /*!< YCbCr 4:2:2 12-bit unpacked BT.709*/
        PixelFormatInfoSelector_YCbCr709_422_12p,    /*!< YCbCr 4:2:2 12-bit packed BT.709*/
        PixelFormatInfoSelector_YCbCr709_422_12p_CbYCrY,    /*!< YCbCr 4:2:2 12-bit packed BT.709*/
        PixelFormatInfoSelector_YUV8_UYV,    /*!< YUV 4:4:4 8-bit*/
        PixelFormatInfoSelector_YUV411_8_UYYVYY,    /*!< YUV 4:1:1 8-bit*/
        PixelFormatInfoSelector_YUV422_8,    /*!< YUV 4:2:2 8-bit*/
        PixelFormatInfoSelector_YUV422_8_UYVY,    /*!< YUV 4:2:2 8-bit*/
        PixelFormatInfoSelector_Polarized8,    /*!< Monochrome Polarized 8-bit*/
        PixelFormatInfoSelector_Polarized10p,    /*!< Monochrome Polarized 10-bit packed*/
        PixelFormatInfoSelector_Polarized12p,    /*!< Monochrome Polarized 12-bit packed*/
        PixelFormatInfoSelector_Polarized16,    /*!< Monochrome Polarized 16-bit*/
        PixelFormatInfoSelector_BayerRGPolarized8,    /*!< Polarized Bayer Red Green filter 8-bit*/
        PixelFormatInfoSelector_BayerRGPolarized10p,    /*!< Polarized Bayer Red Green filter 10-bit packed*/
        PixelFormatInfoSelector_BayerRGPolarized12p,    /*!< Polarized Bayer Red Green filter 12-bit packed*/
        PixelFormatInfoSelector_BayerRGPolarized16,    /*!< Polarized Bayer Red Green filter 16-bit*/
        PixelFormatInfoSelector_LLCMono8,    /*!< Lossless Compression Monochrome 8-bit*/
        PixelFormatInfoSelector_LLCBayerRG8,    /*!< Lossless Compression Bayer Red Green filter 8-bit*/
        PixelFormatInfoSelector_JPEGMono8,    /*!< JPEG Monochrome 8-bit*/
        PixelFormatInfoSelector_JPEGColor8,    /*!< JPEG Color 8-bit*/
        NUM_PIXELFORMATINFOSELECTOR
    };

    enum DeinterlacingEnums    /*!< Controls how the device performs de-interlacing.*/
    {
        Deinterlacing_Off,    /*!< The device doesn't perform de-interlacing.*/
        Deinterlacing_LineDuplication,    /*!< The device performs de-interlacing by outputting each line of each field twice.*/
        Deinterlacing_Weave,    /*!< The device performs de-interlacing by interleaving the lines of all fields.*/
        NUM_DEINTERLACING
    };

    enum ImageCompressionRateOptionEnums    /*!< Two rate controlling options are offered: fixed bit rate or fixed quality. The exact implementation to achieve one or the other is vendor-specific.*/
    {
        ImageCompressionRateOption_FixBitrate,    /*!< Output stream follows a constant bit rate. Allows easy bandwidth management on the link.*/
        ImageCompressionRateOption_FixQuality,    /*!< Output stream has a constant image quality. Can be used when image processing algorithms are sensitive to image degradation caused by excessive data compression.*/
        NUM_IMAGECOMPRESSIONRATEOPTION
    };

    enum ImageCompressionJPEGFormatOptionEnums    /*!< When JPEG is selected as the compression format, a device might optionally offer better control over JPEG-specific options through this feature.*/
    {
        ImageCompressionJPEGFormatOption_Lossless,    /*!< Selects lossless JPEG compression based on a predictive coding model.*/
        ImageCompressionJPEGFormatOption_BaselineStandard,    /*!< Indicates this is a baseline sequential (single-scan) DCT-based JPEG.*/
        ImageCompressionJPEGFormatOption_BaselineOptimized,    /*!< Provides optimized color and slightly better compression than baseline standard by using custom Huffman tables optimized after statistical analysis of the image content.*/
        ImageCompressionJPEGFormatOption_Progressive,    /*!< Indicates this is a progressive (multi-scan) DCT-based JPEG.*/
        NUM_IMAGECOMPRESSIONJPEGFORMATOPTION
    };

    enum AcquisitionStatusSelectorEnums    /*!< Selects the internal acquisition signal to read using AcquisitionStatus.*/
    {
        AcquisitionStatusSelector_AcquisitionTriggerWait,    /*!< Device is currently waiting for a trigger for the capture of one or many frames.*/
        AcquisitionStatusSelector_AcquisitionActive,    /*!< Device is currently doing an acquisition of one or many frames.*/
        AcquisitionStatusSelector_AcquisitionTransfer,    /*!< Device is currently transferring an acquisition of one or many frames.*/
        AcquisitionStatusSelector_FrameTriggerWait,    /*!< Device is currently waiting for a frame start trigger.*/
        AcquisitionStatusSelector_FrameActive,    /*!< Device is currently doing the capture of a frame.*/
        AcquisitionStatusSelector_ExposureActive,    /*!< Device is doing the exposure of a frame.*/
        NUM_ACQUISITIONSTATUSSELECTOR
    };

    enum ExposureTimeModeEnums    /*!< Sets the configuration mode of the ExposureTime feature.*/
    {
        ExposureTimeMode_Common,    /*!< The exposure time is common to all the color components. The common ExposureTime value to use can be set selecting it with ExposureTimeSelector[Common].*/
        ExposureTimeMode_Individual,    /*!< The exposure time is individual for each color component. Each individual ExposureTime values to use can be set by selecting them with ExposureTimeSelector.*/
        NUM_EXPOSURETIMEMODE
    };

    enum ExposureTimeSelectorEnums    /*!< Selects which exposure time is controlled by the ExposureTime feature. This allows for independent control over the exposure components.*/
    {
        ExposureTimeSelector_Common,    /*!< Selects the common ExposureTime.*/
        ExposureTimeSelector_Red,    /*!< Selects the red common ExposureTime.*/
        ExposureTimeSelector_Green,    /*!< Selects the green ExposureTime.*/
        ExposureTimeSelector_Blue,    /*!< Selects the blue ExposureTime.*/
        ExposureTimeSelector_Cyan,    /*!< Selects the cyan common ExposureTime.*/
        ExposureTimeSelector_Magenta,    /*!< Selects the magenta ExposureTime.*/
        ExposureTimeSelector_Yellow,    /*!< Selects the yellow ExposureTime.*/
        ExposureTimeSelector_Infrared,    /*!< Selects the infrared ExposureTime.*/
        ExposureTimeSelector_Ultraviolet,    /*!< Selects the ultraviolet ExposureTime.*/
        ExposureTimeSelector_Stage1,    /*!< Selects the first stage ExposureTime.*/
        ExposureTimeSelector_Stage2,    /*!< Selects the second stage ExposureTime.*/
        NUM_EXPOSURETIMESELECTOR
    };

    enum GainAutoBalanceEnums    /*!< Sets the mode for automatic gain balancing between the sensor color channels or taps. The gain coefficients of each channel or tap are adjusted so they are matched.*/
    {
        GainAutoBalance_Off,    /*!< Gain tap balancing is user controlled using Gain .*/
        GainAutoBalance_Once,    /*!< Gain tap balancing is automatically adjusted once by the device. Once it has converged, it automatically returns to the Off state.*/
        GainAutoBalance_Continuous,    /*!< Gain tap balancing is constantly adjusted by the device.*/
        NUM_GAINAUTOBALANCE
    };

    enum BlackLevelAutoEnums    /*!< Controls the mode for automatic black level adjustment. The exact algorithm used to implement this adjustment is device-specific.*/
    {
        BlackLevelAuto_Off,    /*!< Analog black level is user controlled using BlackLevel.*/
        BlackLevelAuto_Once,    /*!< Analog black level is automatically adjusted once by the device. Once it has converged, it automatically returns to the Off state.*/
        BlackLevelAuto_Continuous,    /*!< Analog black level is constantly adjusted by the device.*/
        NUM_BLACKLEVELAUTO
    };

    enum BlackLevelAutoBalanceEnums    /*!< Controls the mode for automatic black level balancing between the sensor color channels or taps. The black level coefficients of each channel are adjusted so they are matched.*/
    {
        BlackLevelAutoBalance_Off,    /*!< Black level tap balancing is user controlled using BlackLevel.*/
        BlackLevelAutoBalance_Once,    /*!< Black level tap balancing is automatically adjusted once by the device. Once it has converged, it automatically returns to the Off state.*/
        BlackLevelAutoBalance_Continuous,    /*!< Black level tap balancing is constantly adjusted by the device.*/
        NUM_BLACKLEVELAUTOBALANCE
    };

    enum WhiteClipSelectorEnums    /*!< Selects which White Clip to control.*/
    {
        WhiteClipSelector_All,    /*!< White Clip will be applied to all channels or taps.*/
        WhiteClipSelector_Red,    /*!< White Clip will be applied to the red channel.*/
        WhiteClipSelector_Green,    /*!< White Clip will be applied to the green channel.*/
        WhiteClipSelector_Blue,    /*!< White Clip will be applied to the blue channel.*/
        WhiteClipSelector_Y,    /*!< White Clip will be applied to Y channel.*/
        WhiteClipSelector_U,    /*!< White Clip will be applied to U channel.*/
        WhiteClipSelector_V,    /*!< White Clip will be applied to V channel.*/
        WhiteClipSelector_Tap1,    /*!< White Clip will be applied to Tap 1.*/
        WhiteClipSelector_Tap2,    /*!< White Clip will be applied to Tap 2.*/
        NUM_WHITECLIPSELECTOR
    };

    enum TimerSelectorEnums    /*!< Selects which Timer to configure.*/
    {
        TimerSelector_Timer0,    /*!< Selects the Timer 0.*/
        TimerSelector_Timer1,    /*!< Selects the Timer 1.*/
        TimerSelector_Timer2,    /*!< Selects the Timer 2.*/
        NUM_TIMERSELECTOR
    };

    enum TimerStatusEnums    /*!< Returns the current status of the Timer.*/
    {
        TimerStatus_TimerIdle,    /*!< The Timer is idle.*/
        TimerStatus_TimerTriggerWait,    /*!< The Timer is waiting for a start trigger.*/
        TimerStatus_TimerActive,    /*!< The Timer is counting for the specified duration.*/
        TimerStatus_TimerCompleted,    /*!< The Timer reached the TimerDuration count.*/
        NUM_TIMERSTATUS
    };

    enum TimerTriggerSourceEnums    /*!< Selects the source of the trigger to start the Timer.*/
    {
        TimerTriggerSource_Off,    /*!< Disables the Timer trigger.*/
        TimerTriggerSource_AcquisitionTrigger,    /*!< Starts with the reception of the Acquisition Trigger.*/
        TimerTriggerSource_AcquisitionStart,    /*!< Starts with the reception of the Acquisition Start.*/
        TimerTriggerSource_AcquisitionEnd,    /*!< Starts with the reception of the Acquisition End.*/
        TimerTriggerSource_FrameTrigger,    /*!< Starts with the reception of the Frame Start Trigger.*/
        TimerTriggerSource_FrameStart,    /*!< Starts with the reception of the Frame Start.*/
        TimerTriggerSource_FrameEnd,    /*!< Starts with the reception of the Frame End.*/
        TimerTriggerSource_FrameBurstStart,    /*!< Starts with the reception of the Frame Burst Start.*/
        TimerTriggerSource_FrameBurstEnd,    /*!< Starts with the reception of the Frame Burst End.*/
        TimerTriggerSource_LineTrigger,    /*!< Starts with the reception of the Line Start Trigger.*/
        TimerTriggerSource_LineStart,    /*!< Starts with the reception of the Line Start.*/
        TimerTriggerSource_LineEnd,    /*!< Starts with the reception of the Line End.*/
        TimerTriggerSource_ExposureStart,    /*!< Starts with the reception of the Exposure Start.*/
        TimerTriggerSource_ExposureEnd,    /*!< Starts with the reception of the Exposure End.*/
        TimerTriggerSource_Line0,    /*!< Starts when the specidfied TimerTriggerActivation condition is met on the chosen I/O Line.*/
        TimerTriggerSource_Line1,    /*!< Starts when the specidfied TimerTriggerActivation condition is met on the chosen I/O Line.*/
        TimerTriggerSource_Line2,    /*!< Starts when the specidfied TimerTriggerActivation condition is met on the chosen I/O Line.*/
        TimerTriggerSource_UserOutput0,    /*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
        TimerTriggerSource_UserOutput1,    /*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
        TimerTriggerSource_UserOutput2,    /*!< Specifies which User Output bit signal to use as internal source for the trigger.*/
        TimerTriggerSource_Counter0Start,    /*!< Starts with the reception of the Counter Start.*/
        TimerTriggerSource_Counter1Start,    /*!< Starts with the reception of the Counter Start.*/
        TimerTriggerSource_Counter2Start,    /*!< Starts with the reception of the Counter Start.*/
        TimerTriggerSource_Counter0End,    /*!< Starts with the reception of the Counter End.*/
        TimerTriggerSource_Counter1End,    /*!< Starts with the reception of the Counter End.*/
        TimerTriggerSource_Counter2End,    /*!< Starts with the reception of the Counter End.*/
        TimerTriggerSource_Timer0Start,    /*!< Starts with the reception of the Timer Start.*/
        TimerTriggerSource_Timer1Start,    /*!< Starts with the reception of the Timer Start.*/
        TimerTriggerSource_Timer2Start,    /*!< Starts with the reception of the Timer Start.*/
        TimerTriggerSource_Timer0End,    /*!< Starts with the reception of the Timer End. Note that a timer can retrigger itself to achieve a free running Timer.*/
        TimerTriggerSource_Timer1End,    /*!< Starts with the reception of the Timer End. Note that a timer can retrigger itself to achieve a free running Timer.*/
        TimerTriggerSource_Timer2End,    /*!< Starts with the reception of the Timer End. Note that a timer can retrigger itself to achieve a free running Timer.*/
        TimerTriggerSource_Encoder0,    /*!< Starts with the reception of the Encoder output signal.*/
        TimerTriggerSource_Encoder1,    /*!< Starts with the reception of the Encoder output signal.*/
        TimerTriggerSource_Encoder2,    /*!< Starts with the reception of the Encoder output signal.*/
        TimerTriggerSource_SoftwareSignal0,    /*!< Starts on the reception of the Software Signal.*/
        TimerTriggerSource_SoftwareSignal1,    /*!< Starts on the reception of the Software Signal.*/
        TimerTriggerSource_SoftwareSignal2,    /*!< Starts on the reception of the Software Signal.*/
        TimerTriggerSource_Action0,    /*!< Starts with the assertion of the chosen action signal.*/
        TimerTriggerSource_Action1,    /*!< Starts with the assertion of the chosen action signal.*/
        TimerTriggerSource_Action2,    /*!< Starts with the assertion of the chosen action signal.*/
        TimerTriggerSource_LinkTrigger0,    /*!< Starts with the reception of the chosen Link Trigger.*/
        TimerTriggerSource_LinkTrigger1,    /*!< Starts with the reception of the chosen Link Trigger.*/
        TimerTriggerSource_LinkTrigger2,    /*!< Starts with the reception of the chosen Link Trigger.*/
        NUM_TIMERTRIGGERSOURCE
    };

    enum TimerTriggerActivationEnums    /*!< Selects the activation mode of the trigger to start the Timer.*/
    {
        TimerTriggerActivation_RisingEdge,    /*!< Starts counting on the Rising Edge of the selected trigger signal.*/
        TimerTriggerActivation_FallingEdge,    /*!< Starts counting on the Falling Edge of the selected trigger signal.*/
        TimerTriggerActivation_AnyEdge,    /*!< Starts counting on the Falling or Rising Edge of the selected trigger signal.*/
        TimerTriggerActivation_LevelHigh,    /*!< Counts as long as the selected trigger signal level is High.*/
        TimerTriggerActivation_LevelLow,    /*!< Counts as long as the selected trigger signal level is Low.*/
        NUM_TIMERTRIGGERACTIVATION
    };

    enum EncoderSelectorEnums    /*!< Selects which Encoder to configure.*/
    {
        EncoderSelector_Encoder0,    /*!< Selects Encoder 0.*/
        EncoderSelector_Encoder1,    /*!< Selects Encoder 1.*/
        EncoderSelector_Encoder2,    /*!< Selects Encoder 2.*/
        NUM_ENCODERSELECTOR
    };

    enum EncoderSourceAEnums    /*!< Selects the signal which will be the source of the A input of the Encoder.*/
    {
        EncoderSourceA_Off,    /*!< Counter is stopped.*/
        EncoderSourceA_Line0,    /*!< Encoder Forward input is taken from the chosen I/O Line.*/
        EncoderSourceA_Line1,    /*!< Encoder Forward input is taken from the chosen I/O Line.*/
        EncoderSourceA_Line2,    /*!< Encoder Forward input is taken from the chosen I/O Line.*/
        NUM_ENCODERSOURCEA
    };

    enum EncoderSourceBEnums    /*!< Selects the signal which will be the source of the B input of the Encoder.*/
    {
        EncoderSourceB_Off,    /*!< Counter is stopped.*/
        EncoderSourceB_Line0,    /*!< Encoder Reverse input is taken from the chosen I/O Line..*/
        EncoderSourceB_Line1,    /*!< Encoder Reverse input is taken from the chosen I/O Line..*/
        EncoderSourceB_Line2,    /*!< Encoder Reverse input is taken from the chosen I/O Line..*/
        NUM_ENCODERSOURCEB
    };

    enum EncoderModeEnums    /*!< Selects if the count of encoder uses FourPhase mode with jitter filtering or the HighResolution mode without jitter filtering.*/
    {
        EncoderMode_FourPhase,    /*!< The counter increments or decrements 1 for every full quadrature cycle with jitter filtering.*/
        EncoderMode_HighResolution,    /*!< The counter increments or decrements every quadrature phase for high resolution counting, but without jitter filtering.*/
        NUM_ENCODERMODE
    };

    enum EncoderOutputModeEnums    /*!< Selects the conditions for the Encoder interface to generate a valid Encoder output signal.*/
    {
        EncoderOutputMode_Off,    /*!< No output pulse are generated.*/
        EncoderOutputMode_PositionUp,    /*!< Output pulses are generated at all new positions in the positive direction. If the encoder reverses no output pulse are generated until it has again passed the position where the reversal started.*/
        EncoderOutputMode_PositionDown,    /*!< Output pulses are generated at all new positions in the negative direction. If the encoder reverses no output pulse are generated until it has again passed the position where the reversal started.*/
        EncoderOutputMode_DirectionUp,    /*!< Output pulses are generated at all position increments in the positive direction while ignoring negative direction motion.*/
        EncoderOutputMode_DirectionDown,    /*!< Output pulses are generated at all position increments in the negative direction while ignoring positive direction motion.*/
        EncoderOutputMode_Motion,    /*!< Output pulses are generated at all motion increments in both directions.*/
        NUM_ENCODEROUTPUTMODE
    };

    enum EncoderStatusEnums    /*!< Returns the motion status of the encoder.*/
    {
        EncoderStatus_EncoderUp,    /*!< The encoder counter last incremented.*/
        EncoderStatus_EncoderDown,    /*!< The encoder counter last decremented.*/
        EncoderStatus_EncoderIdle,    /*!< The encoder is not active.*/
        EncoderStatus_EncoderStatic,    /*!< No motion within the EncoderTimeout time.*/
        NUM_ENCODERSTATUS
    };

    enum EncoderResetSourceEnums    /*!< Selects the signals that will be the source to reset the Encoder.*/
    {
        EncoderResetSource_Off,    /*!< Disable the Encoder Reset trigger.*/
        EncoderResetSource_AcquisitionTrigger,    /*!< Resets with the reception of the Acquisition Trigger.*/
        EncoderResetSource_AcquisitionStart,    /*!< Resets with the reception of the Acquisition Start.*/
        EncoderResetSource_AcquisitionEnd,    /*!< Resets with the reception of the Acquisition End.*/
        EncoderResetSource_FrameTrigger,    /*!< Resets with the reception of the Frame Start Trigger.*/
        EncoderResetSource_FrameStart,    /*!< Resets with the reception of the Frame Start.*/
        EncoderResetSource_FrameEnd,    /*!< Resets with the reception of the Frame End.*/
        EncoderResetSource_ExposureStart,    /*!< Resets with the reception of the Exposure Start.*/
        EncoderResetSource_ExposureEnd,    /*!< Resets with the reception of the Exposure End.*/
        EncoderResetSource_Line0,    /*!< Resets by the chosen I/O Line.*/
        EncoderResetSource_Line1,    /*!< Resets by the chosen I/O Line.*/
        EncoderResetSource_Line2,    /*!< Resets by the chosen I/O Line.*/
        EncoderResetSource_Counter0Start,    /*!< Resets with the reception of the Counter Start.*/
        EncoderResetSource_Counter1Start,    /*!< Resets with the reception of the Counter Start.*/
        EncoderResetSource_Counter2Start,    /*!< Resets with the reception of the Counter Start.*/
        EncoderResetSource_Counter0End,    /*!< Resets with the reception of the Counter End.*/
        EncoderResetSource_Counter1End,    /*!< Resets with the reception of the Counter End.*/
        EncoderResetSource_Counter2End,    /*!< Resets with the reception of the Counter End.*/
        EncoderResetSource_Timer0Start,    /*!< Resets with the reception of the Timer Start.*/
        EncoderResetSource_Timer1Start,    /*!< Resets with the reception of the Timer Start.*/
        EncoderResetSource_Timer2Start,    /*!< Resets with the reception of the Timer Start.*/
        EncoderResetSource_Timer0End,    /*!< Resets with the reception of the Timer End.*/
        EncoderResetSource_Timer1End,    /*!< Resets with the reception of the Timer End.*/
        EncoderResetSource_Timer2End,    /*!< Resets with the reception of the Timer End.*/
        EncoderResetSource_UserOutput0,    /*!< Resets by the chosen User Output bit.*/
        EncoderResetSource_UserOutput1,    /*!< Resets by the chosen User Output bit.*/
        EncoderResetSource_UserOutput2,    /*!< Resets by the chosen User Output bit.*/
        EncoderResetSource_SoftwareSignal0,    /*!< Resets on the reception of the Software Signal.*/
        EncoderResetSource_SoftwareSignal1,    /*!< Resets on the reception of the Software Signal.*/
        EncoderResetSource_SoftwareSignal2,    /*!< Resets on the reception of the Software Signal.*/
        EncoderResetSource_Action0,    /*!< Resets on assertions of the chosen action signal (Broadcasted signal on the transport layer).*/
        EncoderResetSource_Action1,    /*!< Resets on assertions of the chosen action signal (Broadcasted signal on the transport layer).*/
        EncoderResetSource_Action2,    /*!< Resets on assertions of the chosen action signal (Broadcasted signal on the transport layer).*/
        EncoderResetSource_LinkTrigger0,    /*!< Resets on the reception of the chosen Link Trigger (received from the transport layer).*/
        EncoderResetSource_LinkTrigger1,    /*!< Resets on the reception of the chosen Link Trigger (received from the transport layer).*/
        EncoderResetSource_LinkTrigger2,    /*!< Resets on the reception of the chosen Link Trigger (received from the transport layer).*/
        NUM_ENCODERRESETSOURCE
    };

    enum EncoderResetActivationEnums    /*!< Selects the Activation mode of the Encoder Reset Source signal.*/
    {
        EncoderResetActivation_RisingEdge,    /*!< Resets the Encoder on the Rising Edge of the signal.*/
        EncoderResetActivation_FallingEdge,    /*!< Resets the Encoder on the Falling Edge of the signal.*/
        EncoderResetActivation_AnyEdge,    /*!< Resets the Encoder on the Falling or rising Edge of the selected signal.*/
        EncoderResetActivation_LevelHigh,    /*!< Resets the Encoder as long as the selected signal level is High.*/
        EncoderResetActivation_LevelLow,    /*!< Resets the Encoder as long as the selected signal level is Low.*/
        NUM_ENCODERRESETACTIVATION
    };

    enum SoftwareSignalSelectorEnums    /*!< Selects which Software Signal features to control.*/
    {
        SoftwareSignalSelector_SoftwareSignal0,    /*!< Selects the software generated signal to control.*/
        SoftwareSignalSelector_SoftwareSignal1,    /*!< Selects the software generated signal to control.*/
        SoftwareSignalSelector_SoftwareSignal2,    /*!< Selects the software generated signal to control.*/
        NUM_SOFTWARESIGNALSELECTOR
    };

    enum ActionUnconditionalModeEnums    /*!< Enables the unconditional action command mode where action commands are processed even when the primary control channel is closed.*/
    {
        ActionUnconditionalMode_Off,    /*!< Unconditional mode is disabled.*/
        ActionUnconditionalMode_On,    /*!< Unconditional mode is enabled.*/
        NUM_ACTIONUNCONDITIONALMODE
    };

    enum SourceSelectorEnums    /*!< Selects the source to control.*/
    {
        SourceSelector_Source0,    /*!< Selects the data source 0.*/
        SourceSelector_Source1,    /*!< Selects the data source 1.*/
        SourceSelector_Source2,    /*!< Selects the data source 2.*/
        SourceSelector_All,    /*!< Selects all the data sources.*/
        NUM_SOURCESELECTOR
    };

    enum TransferSelectorEnums    /*!< Selects which stream transfers are currently controlled by the selected Transfer features.*/
    {
        TransferSelector_Stream0,    /*!< The transfer features control the data stream 0.*/
        TransferSelector_Stream1,    /*!< The transfer features control the data stream 1.*/
        TransferSelector_Stream2,    /*!< The transfer features control the data stream 2.*/
        TransferSelector_All,    /*!< The transfer features control all the data streams simulateneously.*/
        NUM_TRANSFERSELECTOR
    };

    enum TransferTriggerSelectorEnums    /*!< Selects the type of transfer trigger to configure.*/
    {
        TransferTriggerSelector_TransferStart,    /*!< Selects a trigger to start the transfers.*/
        TransferTriggerSelector_TransferStop,    /*!< Selects a trigger to stop the transfers.*/
        TransferTriggerSelector_TransferAbort,    /*!< Selects a trigger to abort the transfers.*/
        TransferTriggerSelector_TransferPause,    /*!< Selects a trigger to pause the transfers.*/
        TransferTriggerSelector_TransferResume,    /*!< Selects a trigger to Resume the transfers.*/
        TransferTriggerSelector_TransferActive,    /*!< Selects a trigger to Activate the transfers. This trigger type is used when TriggerActivation is set LevelHigh or levelLow.*/
        TransferTriggerSelector_TransferBurstStart,    /*!< Selects a trigger to start the transfer of a burst of frames specified by TransferBurstCount.*/
        TransferTriggerSelector_TransferBurstStop,    /*!< Selects a trigger to end the transfer of a burst of frames.*/
        NUM_TRANSFERTRIGGERSELECTOR
    };

    enum TransferTriggerModeEnums    /*!< Controls if the selected trigger is active.*/
    {
        TransferTriggerMode_Off,    /*!< Disables the selected trigger.*/
        TransferTriggerMode_On,    /*!< Enable the selected trigger.*/
        NUM_TRANSFERTRIGGERMODE
    };

    enum TransferTriggerSourceEnums    /*!< Specifies the signal to use as the trigger source for transfers.*/
    {
        TransferTriggerSource_Line0,    /*!< Specifies which physical line (or pin) and associated I/O control block to use as external source for the transfer control trigger signal.*/
        TransferTriggerSource_Line1,    /*!< Specifies which physical line (or pin) and associated I/O control block to use as external source for the transfer control trigger signal.*/
        TransferTriggerSource_Line2,    /*!< Specifies which physical line (or pin) and associated I/O control block to use as external source for the transfer control trigger signal.*/
        TransferTriggerSource_Counter0Start,    /*!< Specifies which of the Counter signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_Counter1Start,    /*!< Specifies which of the Counter signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_Counter2Start,    /*!< Specifies which of the Counter signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_Counter0End,    /*!< Specifies which of the Counter signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_Counter1End,    /*!< Specifies which of the Counter signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_Counter2End,    /*!< Specifies which of the Counter signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_Timer0Start,    /*!< Specifies which Timer signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_Timer1Start,    /*!< Specifies which Timer signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_Timer2Start,    /*!< Specifies which Timer signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_Timer0End,    /*!< Specifies which Timer signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_Timer1End,    /*!< Specifies which Timer signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_Timer2End,    /*!< Specifies which Timer signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_SoftwareSignal0,    /*!< Specifies which Software Signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_SoftwareSignal1,    /*!< Specifies which Software Signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_SoftwareSignal2,    /*!< Specifies which Software Signal to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_Action0,    /*!< Specifies which Action command to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_Action1,    /*!< Specifies which Action command to use as internal source for the transfer control trigger signal.*/
        TransferTriggerSource_Action2,    /*!< Specifies which Action command to use as internal source for the transfer control trigger signal.*/
        NUM_TRANSFERTRIGGERSOURCE
    };

    enum TransferTriggerActivationEnums    /*!< Specifies the activation mode of the transfer control trigger.*/
    {
        TransferTriggerActivation_RisingEdge,    /*!< Specifies that the trigger is considered valid on the rising edge of the source signal.*/
        TransferTriggerActivation_FallingEdge,    /*!< Specifies that the trigger is considered valid on the falling edge of the source signal.*/
        TransferTriggerActivation_AnyEdge,    /*!< Specifies that the trigger is considered valid on the falling or rising edge of the source signal.*/
        TransferTriggerActivation_LevelHigh,    /*!< Specifies that the trigger is considered valid as long as the level of the source signal is high. This can apply to TransferActive and TransferPause trigger.*/
        TransferTriggerActivation_LevelLow,    /*!< Specifies that the trigger is considered valid as long as the level of the source signal is low. This can apply to TransferActive and TransferPause trigger.*/
        NUM_TRANSFERTRIGGERACTIVATION
    };

    enum TransferStatusSelectorEnums    /*!< Selects which status of the transfer module to read.*/
    {
        TransferStatusSelector_Streaming,    /*!< Data blocks are transmitted when enough data is available.*/
        TransferStatusSelector_Paused,    /*!< Data blocks transmission is suspended immediately.*/
        TransferStatusSelector_Stopping,    /*!< Data blocks transmission is stopping. The current block transmission will be completed and the transfer state will stop.*/
        TransferStatusSelector_Stopped,    /*!< Data blocks transmission is stopped.*/
        TransferStatusSelector_QueueOverflow,    /*!< Data blocks queue is in overflow state.*/
        NUM_TRANSFERSTATUSSELECTOR
    };

    enum TransferComponentSelectorEnums    /*!< Selects the color component for the control of the TransferStreamChannel feature.*/
    {
        TransferComponentSelector_Red,    /*!< The TransferStreamChannel feature controls the index of the stream channel for the streaming of the red plane of the planar pixel formats.*/
        TransferComponentSelector_Green,    /*!< The TransferStreamChannel feature controls the index of the stream channel for the streaming of the green plane of the planar pixel formats.*/
        TransferComponentSelector_Blue,    /*!< The TransferStreamChannel feature controls the index of the stream channel for the streaming of blue plane of the planar pixel formats.*/
        TransferComponentSelector_All,    /*!< The TransferStreamChannel feature controls the index of the stream channel for the streaming of all the planes of the planar pixel formats simultaneously or non planar pixel formats.*/
        NUM_TRANSFERCOMPONENTSELECTOR
    };

    enum Scan3dDistanceUnitEnums    /*!< Specifies the unit used when delivering calibrated distance data.*/
    {
        Scan3dDistanceUnit_Millimeter,    /*!< Distance values are in millimeter units (default).*/
        Scan3dDistanceUnit_Inch,    /*!< Distance values are in inch units.*/
        NUM_SCAN3DDISTANCEUNIT
    };

    enum Scan3dCoordinateSystemEnums    /*!< Specifies the Coordinate system to use for the device.*/
    {
        Scan3dCoordinateSystem_Cartesian,    /*!< Default value. 3-axis orthogonal, right-hand X-Y-Z.*/
        Scan3dCoordinateSystem_Spherical,    /*!< A Theta-Phi-Rho coordinate system.*/
        Scan3dCoordinateSystem_Cylindrical,    /*!< A Theta-Y-Rho coordinate system.*/
        NUM_SCAN3DCOORDINATESYSTEM
    };

    enum Scan3dOutputModeEnums    /*!< Controls the Calibration and data organization of the device, naming the coordinates transmitted.*/
    {
        Scan3dOutputMode_UncalibratedC,    /*!< Uncalibrated 2.5D Depth map. The distance data does not represent a physical unit and may be non-linear. The data is a 2.5D range map only.*/
        Scan3dOutputMode_CalibratedABC_Grid,    /*!< 3 Coordinates in grid organization. The full 3 coordinate data with the grid array organization from the sensor kept.*/
        Scan3dOutputMode_CalibratedABC_PointCloud,    /*!< 3 Coordinates without organization. The full 3 coordinate data without any organization of data points. Typically only valid points transmitted giving varying image size.*/
        Scan3dOutputMode_CalibratedAC,    /*!< 2 Coordinates with fixed B sampling. The data is sent as a A and C coordinates (X,Z or Theta,Rho). The B (Y) axis uses the scale and offset parameters for the B axis.*/
        Scan3dOutputMode_CalibratedAC_Linescan,    /*!< 2 Coordinates with varying sampling. The data is sent as a A and C coordinates (X,Z or Theta,Rho). The B (Y) axis comes from the encoder chunk value.*/
        Scan3dOutputMode_CalibratedC,    /*!< Calibrated 2.5D Depth map. The distance data is expressed in the chosen distance unit. The data is a 2.5D range map. No information on X-Y axes available.*/
        Scan3dOutputMode_CalibratedC_Linescan,    /*!< Depth Map with varying B sampling. The distance data is expressed in the chosen distance unit. The data is a 2.5D range map. The B (Y) axis comes from the encoder chunk value.*/
        Scan3dOutputMode_RectifiedC,    /*!< Rectified 2.5D Depth map. The distance data has been rectified to a uniform sampling pattern in the X and Y direction. The data is a 2.5D range map only. If a complete 3D point cloud is rectified but transmitted as explicit coordinates it should be transmitted as one of the "CalibratedABC" formats.*/
        Scan3dOutputMode_RectifiedC_Linescan,    /*!< Rectified 2.5D Depth map with varying B sampling. The data is sent as rectified 1D profiles using Coord3D_C pixels. The B (Y) axis comes from the encoder chunk value.*/
        Scan3dOutputMode_DisparityC,    /*!< Disparity 2.5D Depth map. The distance is inversely proportional to the pixel (disparity) value.*/
        Scan3dOutputMode_DisparityC_Linescan,    /*!< Disparity 2.5D Depth map with varying B sampling. The distance is inversely proportional to the pixel (disparity) value. The B (Y) axis comes from the encoder chunk value.*/
        NUM_SCAN3DOUTPUTMODE
    };

    enum Scan3dCoordinateSystemReferenceEnums    /*!< Defines coordinate system reference location.*/
    {
        Scan3dCoordinateSystemReference_Anchor,    /*!< Default value. Original fixed reference. The coordinate system fixed relative the camera reference point marker is used.*/
        Scan3dCoordinateSystemReference_Transformed,    /*!< Transformed reference system. The transformed coordinate system is used according to the definition in the rotation and translation matrices.*/
        NUM_SCAN3DCOORDINATESYSTEMREFERENCE
    };

    enum Scan3dCoordinateSelectorEnums    /*!< Selects the individual coordinates in the vectors for 3D information/transformation.*/
    {
        Scan3dCoordinateSelector_CoordinateA,    /*!< The first (X or Theta) coordinate*/
        Scan3dCoordinateSelector_CoordinateB,    /*!< The second (Y or Phi) coordinate*/
        Scan3dCoordinateSelector_CoordinateC,    /*!< The third (Z or Rho) coordinate.*/
        NUM_SCAN3DCOORDINATESELECTOR
    };

    enum Scan3dCoordinateTransformSelectorEnums    /*!< Sets the index to read/write a coordinate transform value.*/
    {
        Scan3dCoordinateTransformSelector_RotationX,    /*!< Rotation around X axis.*/
        Scan3dCoordinateTransformSelector_RotationY,    /*!< Rotation around Y axis.*/
        Scan3dCoordinateTransformSelector_RotationZ,    /*!< Rotation around Z axis.*/
        Scan3dCoordinateTransformSelector_TranslationX,    /*!< Translation along X axis.*/
        Scan3dCoordinateTransformSelector_TranslationY,    /*!< Translation along Y axis.*/
        Scan3dCoordinateTransformSelector_TranslationZ,    /*!< Translation along Z axis.*/
        NUM_SCAN3DCOORDINATETRANSFORMSELECTOR
    };

    enum Scan3dCoordinateReferenceSelectorEnums    /*!< Sets the index to read a coordinate system reference value defining the transform of a point from the current (Anchor or Transformed) system to the reference system.*/
    {
        Scan3dCoordinateReferenceSelector_RotationX,    /*!< Rotation around X axis.*/
        Scan3dCoordinateReferenceSelector_RotationY,    /*!< Rotation around Y axis.*/
        Scan3dCoordinateReferenceSelector_RotationZ,    /*!< Rotation around Z axis.*/
        Scan3dCoordinateReferenceSelector_TranslationX,    /*!< X axis translation.*/
        Scan3dCoordinateReferenceSelector_TranslationY,    /*!< Y axis translation.*/
        Scan3dCoordinateReferenceSelector_TranslationZ,    /*!< Z axis translation.*/
        NUM_SCAN3DCOORDINATEREFERENCESELECTOR
    };

    enum ChunkImageComponentEnums    /*!< Returns the component of the payload image. This can be used to identify the image component of a generic part in a multipart transfer.*/
    {
        ChunkImageComponent_Intensity,    /*!< The image data is the intensity component.*/
        ChunkImageComponent_Color,    /*!< The image data is color component.*/
        ChunkImageComponent_Infrared,    /*!< The image data is infrared component.*/
        ChunkImageComponent_Ultraviolet,    /*!< The image data is the ultraviolet component.*/
        ChunkImageComponent_Range,    /*!< The image data is the range (distance) component.*/
        ChunkImageComponent_Disparity,    /*!< The image data is the disparity component.*/
        ChunkImageComponent_Confidence,    /*!< The image data is the confidence map component.*/
        ChunkImageComponent_Scatter,    /*!< The image data is the scatter component.*/
        NUM_CHUNKIMAGECOMPONENT
    };

    enum ChunkCounterSelectorEnums    /*!< Selects which counter to retrieve data from.*/
    {
        ChunkCounterSelector_Counter0,    /*!< Selects the counter 0.*/
        ChunkCounterSelector_Counter1,    /*!< Selects the counter 1.*/
        ChunkCounterSelector_Counter2,    /*!< Selects the counter 2.*/
        NUM_CHUNKCOUNTERSELECTOR
    };

    enum ChunkTimerSelectorEnums    /*!< Selects which Timer to retrieve data from.*/
    {
        ChunkTimerSelector_Timer0,    /*!< Selects the first Timer.*/
        ChunkTimerSelector_Timer1,    /*!< Selects the first Timer.*/
        ChunkTimerSelector_Timer2,    /*!< Selects the second Timer.*/
        NUM_CHUNKTIMERSELECTOR
    };

    enum ChunkEncoderSelectorEnums    /*!< Selects which Encoder to retrieve data from.*/
    {
        ChunkEncoderSelector_Encoder0,    /*!< Selects the first Encoder.*/
        ChunkEncoderSelector_Encoder1,    /*!< Selects the first Encoder.*/
        ChunkEncoderSelector_Encoder2,    /*!< Selects the second Encoder.*/
        NUM_CHUNKENCODERSELECTOR
    };

    enum ChunkEncoderStatusEnums    /*!< Returns the motion status of the selected encoder.*/
    {
        ChunkEncoderStatus_EncoderUp,    /*!< The encoder counter last incremented.*/
        ChunkEncoderStatus_EncoderDown,    /*!< The encoder counter last decremented.*/
        ChunkEncoderStatus_EncoderIdle,    /*!< The encoder is not active.*/
        ChunkEncoderStatus_EncoderStatic,    /*!< No motion within the EncoderTimeout time.*/
        NUM_CHUNKENCODERSTATUS
    };

    enum ChunkExposureTimeSelectorEnums    /*!< Selects which exposure time is read by the ChunkExposureTime feature.*/
    {
        ChunkExposureTimeSelector_Common,    /*!< Selects the common ExposureTime.*/
        ChunkExposureTimeSelector_Red,    /*!< Selects the red common ExposureTime.*/
        ChunkExposureTimeSelector_Green,    /*!< Selects the green ExposureTime.*/
        ChunkExposureTimeSelector_Blue,    /*!< Selects the blue ExposureTime.*/
        ChunkExposureTimeSelector_Cyan,    /*!< Selects the cyan common ExposureTime..*/
        ChunkExposureTimeSelector_Magenta,    /*!< Selects the magenta ExposureTime..*/
        ChunkExposureTimeSelector_Yellow,    /*!< Selects the yellow ExposureTime..*/
        ChunkExposureTimeSelector_Infrared,    /*!< Selects the infrared ExposureTime.*/
        ChunkExposureTimeSelector_Ultraviolet,    /*!< Selects the ultraviolet ExposureTime.*/
        ChunkExposureTimeSelector_Stage1,    /*!< Selects the first stage ExposureTime.*/
        ChunkExposureTimeSelector_Stage2,    /*!< Selects the second stage ExposureTime.*/
        NUM_CHUNKEXPOSURETIMESELECTOR
    };

    enum ChunkSourceIDEnums    /*!< Returns the identifier of Source that the image comes from.*/
    {
        ChunkSourceID_Source0,    /*!< Image comes from the Source 0.*/
        ChunkSourceID_Source1,    /*!< Image comes from the Source 1.*/
        ChunkSourceID_Source2,    /*!< Image comes from the Source 2.*/
        NUM_CHUNKSOURCEID
    };

    enum ChunkRegionIDEnums    /*!< Returns the identifier of Region that the image comes from.*/
    {
        ChunkRegionID_Region0,    /*!< Image comes from the Region 0.*/
        ChunkRegionID_Region1,    /*!< Image comes from the Region 1.*/
        ChunkRegionID_Region2,    /*!< Image comes from the Region 2.*/
        NUM_CHUNKREGIONID
    };

    enum ChunkTransferStreamIDEnums    /*!< Returns identifier of the stream that generated this block.*/
    {
        ChunkTransferStreamID_Stream0,    /*!< Data comes from Stream0.*/
        ChunkTransferStreamID_Stream1,    /*!< Data comes from Stream1.*/
        ChunkTransferStreamID_Stream2,    /*!< Data comes from Stream2.*/
        ChunkTransferStreamID_Stream3,    /*!< Data comes from Stream3.*/
        NUM_CHUNKTRANSFERSTREAMID
    };

    enum ChunkScan3dDistanceUnitEnums    /*!< Returns the Distance Unit of the payload image.*/
    {
        ChunkScan3dDistanceUnit_Millimeter,    /*!< Default value. Distance values are in millimeter units.*/
        ChunkScan3dDistanceUnit_Inch,    /*!< Distance values are in inch units.*/
        NUM_CHUNKSCAN3DDISTANCEUNIT
    };

    enum ChunkScan3dOutputModeEnums    /*!< Returns the Calibrated Mode of the payload image.*/
    {
        ChunkScan3dOutputMode_UncalibratedC,    /*!< Uncalibrated 2.5D Depth map. The distance data does not represent a physical unit and may be non-linear. The data is a 2.5D range map only.*/
        ChunkScan3dOutputMode_CalibratedABC_Grid,    /*!< 3 Coordinates in grid organization. The full 3 coordinate data with the grid array organization from the sensor kept.*/
        ChunkScan3dOutputMode_CalibratedABC_PointCloud,    /*!< 3 Coordinates without organization. The full 3 coordinate data without any organization of data points. Typically only valid points transmitted giving varying image size.*/
        ChunkScan3dOutputMode_CalibratedAC,    /*!< 2 Coordinates with fixed B sampling. The data is sent as a A and C coordinates (X,Z or Theta,Rho). The B (Y) axis uses the scale and offset parameters for the B axis.*/
        ChunkScan3dOutputMode_CalibratedAC_Linescan,    /*!< 2 Coordinates with varying sampling. The data is sent as a A and C coordinates (X,Z or Theta,Rho). The B (Y) axis comes from the encoder chunk value.*/
        ChunkScan3dOutputMode_CalibratedC,    /*!< Calibrated 2.5D Depth map. The distance data is expressed in the chosen distance unit. The data is a 2.5D range map. No information on X-Y axes available.*/
        ChunkScan3dOutputMode_CalibratedC_Linescan,    /*!< Depth Map with varying B sampling. The distance data is expressed in the chosen distance unit. The data is a 2.5D range map. The B (Y) axis comes from the encoder chunk value.*/
        ChunkScan3dOutputMode_RectifiedC,    /*!< Rectified 2.5D Depth map. The distance data has been rectified to a uniform sampling pattern in the X and Y direction. The data is a 2.5D range map only. If a complete 3D point cloud is rectified but transmitted as explicit coordinates it should be transmitted as one of the "CalibratedABC" formats.*/
        ChunkScan3dOutputMode_RectifiedC_Linescan,    /*!< Rectified 2.5D Depth map with varying B sampling. The data is sent as rectified 1D profiles using Coord3D_C pixels. The B (Y) axis comes from the encoder chunk value.*/
        ChunkScan3dOutputMode_DisparityC,    /*!< Disparity 2.5D Depth map. The distance is inversely proportional to the pixel (disparity) value.*/
        ChunkScan3dOutputMode_DisparityC_Linescan,    /*!< Disparity 2.5D Depth map with varying B sampling. The distance is inversely proportional to the pixel (disparity) value. The B (Y) axis comes from the encoder chunk value.*/
        NUM_CHUNKSCAN3DOUTPUTMODE
    };

    enum ChunkScan3dCoordinateSystemEnums    /*!< Returns the Coordinate System of the image included in the payload.*/
    {
        ChunkScan3dCoordinateSystem_Cartesian,    /*!< Default value. 3-axis orthogonal, right-hand X-Y-Z.*/
        ChunkScan3dCoordinateSystem_Spherical,    /*!< A Theta-Phi-Rho coordinate system.*/
        ChunkScan3dCoordinateSystem_Cylindrical,    /*!< A Theta-Y-Rho coordinate system.*/
        NUM_CHUNKSCAN3DCOORDINATESYSTEM
    };

    enum ChunkScan3dCoordinateSystemReferenceEnums    /*!< Returns the Coordinate System Position of the image included in the payload.*/
    {
        ChunkScan3dCoordinateSystemReference_Anchor,    /*!< Default value. Original fixed reference. The coordinate system fixed relative the camera reference point marker is used.*/
        ChunkScan3dCoordinateSystemReference_Transformed,    /*!< Transformed reference system. The transformed coordinate system is used according to the definition in the rotation and translation matrices.*/
        NUM_CHUNKSCAN3DCOORDINATESYSTEMREFERENCE
    };

    enum ChunkScan3dCoordinateSelectorEnums    /*!< Selects which Coordinate to retrieve data from.*/
    {
        ChunkScan3dCoordinateSelector_CoordinateA,    /*!< The first (X or Theta) coordinate*/
        ChunkScan3dCoordinateSelector_CoordinateB,    /*!< The second (Y or Phi) coordinate*/
        ChunkScan3dCoordinateSelector_CoordinateC,    /*!< The third (Z or Rho) coordinate.*/
        NUM_CHUNKSCAN3DCOORDINATESELECTOR
    };

    enum ChunkScan3dCoordinateTransformSelectorEnums    /*!< Selector for transform values.*/
    {
        ChunkScan3dCoordinateTransformSelector_RotationX,    /*!< Rotation around X axis.*/
        ChunkScan3dCoordinateTransformSelector_RotationY,    /*!< Rotation around Y axis.*/
        ChunkScan3dCoordinateTransformSelector_RotationZ,    /*!< Rotation around Z axis.*/
        ChunkScan3dCoordinateTransformSelector_TranslationX,    /*!< Translation along X axis.*/
        ChunkScan3dCoordinateTransformSelector_TranslationY,    /*!< Translation along Y axis.*/
        ChunkScan3dCoordinateTransformSelector_TranslationZ,    /*!< Translation along Z axis.*/
        NUM_CHUNKSCAN3DCOORDINATETRANSFORMSELECTOR
    };

    enum ChunkScan3dCoordinateReferenceSelectorEnums    /*!< Selector to read a coordinate system reference value defining the transform of a point from one system to the other.*/
    {
        ChunkScan3dCoordinateReferenceSelector_RotationX,    /*!< Rotation around X axis.*/
        ChunkScan3dCoordinateReferenceSelector_RotationY,    /*!< Rotation around Y axis.*/
        ChunkScan3dCoordinateReferenceSelector_RotationZ,    /*!< Rotation around Z axis.*/
        ChunkScan3dCoordinateReferenceSelector_TranslationX,    /*!< X axis translation.*/
        ChunkScan3dCoordinateReferenceSelector_TranslationY,    /*!< Y axis translation.*/
        ChunkScan3dCoordinateReferenceSelector_TranslationZ,    /*!< Z axis translation.*/
        NUM_CHUNKSCAN3DCOORDINATEREFERENCESELECTOR
    };

    enum DeviceTapGeometryEnums    /*!< This device tap geometry feature describes the geometrical properties characterizing the taps of a camera as presented at the output of the device.*/
    {
        DeviceTapGeometry_Geometry_1X_1Y,    /*!< Geometry_1X_1Y*/
        DeviceTapGeometry_Geometry_1X2_1Y,    /*!< Geometry_1X2_1Y*/
        DeviceTapGeometry_Geometry_1X2_1Y2,    /*!< Geometry_1X2_1Y2*/
        DeviceTapGeometry_Geometry_2X_1Y,    /*!< Geometry_2X_1Y*/
        DeviceTapGeometry_Geometry_2X_1Y2Geometry_2XE_1Y,    /*!< Geometry_2X_1Y2Geometry_2XE_1Y*/
        DeviceTapGeometry_Geometry_2XE_1Y2,    /*!< Geometry_2XE_1Y2*/
        DeviceTapGeometry_Geometry_2XM_1Y,    /*!< Geometry_2XM_1Y*/
        DeviceTapGeometry_Geometry_2XM_1Y2,    /*!< Geometry_2XM_1Y2*/
        DeviceTapGeometry_Geometry_1X_1Y2,    /*!< Geometry_1X_1Y2*/
        DeviceTapGeometry_Geometry_1X_2YE,    /*!< Geometry_1X_2YE*/
        DeviceTapGeometry_Geometry_1X3_1Y,    /*!< Geometry_1X3_1Y*/
        DeviceTapGeometry_Geometry_3X_1Y,    /*!< Geometry_3X_1Y*/
        DeviceTapGeometry_Geometry_1X,    /*!< Geometry_1X*/
        DeviceTapGeometry_Geometry_1X2,    /*!< Geometry_1X2*/
        DeviceTapGeometry_Geometry_2X,    /*!< Geometry_2X*/
        DeviceTapGeometry_Geometry_2XE,    /*!< Geometry_2XE*/
        DeviceTapGeometry_Geometry_2XM,    /*!< Geometry_2XM*/
        DeviceTapGeometry_Geometry_1X3,    /*!< Geometry_1X3*/
        DeviceTapGeometry_Geometry_3X,    /*!< Geometry_3X*/
        DeviceTapGeometry_Geometry_1X4_1Y,    /*!< Geometry_1X4_1Y*/
        DeviceTapGeometry_Geometry_4X_1Y,    /*!< Geometry_4X_1Y*/
        DeviceTapGeometry_Geometry_2X2_1Y,    /*!< Geometry_2X2_1Y*/
        DeviceTapGeometry_Geometry_2X2E_1YGeometry_2X2M_1Y,    /*!< Geometry_2X2E_1YGeometry_2X2M_1Y*/
        DeviceTapGeometry_Geometry_1X2_2YE,    /*!< Geometry_1X2_2YE*/
        DeviceTapGeometry_Geometry_2X_2YE,    /*!< Geometry_2X_2YE*/
        DeviceTapGeometry_Geometry_2XE_2YE,    /*!< Geometry_2XE_2YE*/
        DeviceTapGeometry_Geometry_2XM_2YE,    /*!< Geometry_2XM_2YE*/
        DeviceTapGeometry_Geometry_1X4,    /*!< Geometry_1X4*/
        DeviceTapGeometry_Geometry_4X,    /*!< Geometry_4X*/
        DeviceTapGeometry_Geometry_2X2,    /*!< Geometry_2X2*/
        DeviceTapGeometry_Geometry_2X2E,    /*!< Geometry_2X2E*/
        DeviceTapGeometry_Geometry_2X2M,    /*!< Geometry_2X2M*/
        DeviceTapGeometry_Geometry_1X8_1Y,    /*!< Geometry_1X8_1Y*/
        DeviceTapGeometry_Geometry_8X_1Y,    /*!< Geometry_8X_1Y*/
        DeviceTapGeometry_Geometry_4X2_1Y,    /*!< Geometry_4X2_1Y*/
        DeviceTapGeometry_Geometry_2X2E_2YE,    /*!< Geometry_2X2E_2YE*/
        DeviceTapGeometry_Geometry_1X8,    /*!< Geometry_1X8*/
        DeviceTapGeometry_Geometry_8X,    /*!< Geometry_8X*/
        DeviceTapGeometry_Geometry_4X2,    /*!< Geometry_4X2*/
        DeviceTapGeometry_Geometry_4X2E,    /*!< Geometry_4X2E*/
        DeviceTapGeometry_Geometry_4X2E_1Y,    /*!< Geometry_4X2E_1Y*/
        DeviceTapGeometry_Geometry_1X10_1Y,    /*!< Geometry_1X10_1Y*/
        DeviceTapGeometry_Geometry_10X_1Y,    /*!< Geometry_10X_1Y*/
        DeviceTapGeometry_Geometry_1X10,    /*!< Geometry_1X10*/
        DeviceTapGeometry_Geometry_10X,    /*!< Geometry_10X*/
        NUM_DEVICETAPGEOMETRY
    };

    enum GevPhysicalLinkConfigurationEnums    /*!< Controls the principal physical link configuration to use on next restart/power-up of the device.*/
    {
        GevPhysicalLinkConfiguration_SingleLink,    /*!< Single Link*/
        GevPhysicalLinkConfiguration_MultiLink,    /*!< Multi Link*/
        GevPhysicalLinkConfiguration_StaticLAG,    /*!< Static LAG*/
        GevPhysicalLinkConfiguration_DynamicLAG,    /*!< Dynamic LAG*/
        NUM_GEVPHYSICALLINKCONFIGURATION
    };

    enum GevCurrentPhysicalLinkConfigurationEnums    /*!< Indicates the current physical link configuration of the device.*/
    {
        GevCurrentPhysicalLinkConfiguration_SingleLink,    /*!< Single Link*/
        GevCurrentPhysicalLinkConfiguration_MultiLink,    /*!< Multi Link*/
        GevCurrentPhysicalLinkConfiguration_StaticLAG,    /*!< Static LAG*/
        GevCurrentPhysicalLinkConfiguration_DynamicLAG,    /*!< Dynamic LAG*/
        NUM_GEVCURRENTPHYSICALLINKCONFIGURATION
    };

    enum GevIPConfigurationStatusEnums    /*!< Reports the current IP configuration status.*/
    {
        GevIPConfigurationStatus_None,    /*!< None*/
        GevIPConfigurationStatus_PersistentIP,    /*!< Persistent IP*/
        GevIPConfigurationStatus_DHCP,    /*!< DHCP*/
        GevIPConfigurationStatus_LLA,    /*!< LLA*/
        GevIPConfigurationStatus_ForceIP,    /*!< Force IP*/
        NUM_GEVIPCONFIGURATIONSTATUS
    };

    enum GevGVCPExtendedStatusCodesSelectorEnums    /*!< Selects the GigE Vision version to control extended status codes for.*/
    {
        GevGVCPExtendedStatusCodesSelector_Version1_1,    /*!< Version 1 1*/
        GevGVCPExtendedStatusCodesSelector_Version2_0,    /*!< Version 2 0*/
        NUM_GEVGVCPEXTENDEDSTATUSCODESSELECTOR
    };

    enum GevGVSPExtendedIDModeEnums    /*!< Enables the extended IDs mode.*/
    {
        GevGVSPExtendedIDMode_Off,    /*!< Off*/
        GevGVSPExtendedIDMode_On,    /*!< On*/
        NUM_GEVGVSPEXTENDEDIDMODE
    };

    enum ClConfigurationEnums    /*!< This Camera Link specific feature describes the configuration used by the camera. It helps especially when a camera is capable of operation in a non-standard configuration, and when the features PixelSize, SensorDigitizationTaps, and DeviceTapGeometry do not provide enough information for interpretation of the image data provided by the camera.*/
    {
        ClConfiguration_Base,    /*!< Standard base configuration described by the Camera Link standard.*/
        ClConfiguration_Medium,    /*!< Standard medium configuration described by the Camera Link standard.*/
        ClConfiguration_Full,    /*!< Standard full configuration described by the Camera Link standard.*/
        ClConfiguration_DualBase,    /*!< The camera streams the data from multiple taps (that do not fit in the standard base configuration) through two Camera Link base ports. It is responsibility of the application or frame grabber to reconstruct the full image. Only one of the ports (fixed) serves as the "master" for serial communication and triggering.*/
        ClConfiguration_EightyBit,    /*!< Standard 80-bit configuration with 10 taps of 8 bits or 8 taps of 10 bits, as described by the Camera Link standard.*/
        NUM_CLCONFIGURATION
    };

    enum ClTimeSlotsCountEnums    /*!< This Camera Link specific feature describes the time multiplexing of the camera link connection to transfer more than the configuration allows, in one single clock.*/
    {
        ClTimeSlotsCount_One,    /*!< One*/
        ClTimeSlotsCount_Two,    /*!< Two*/
        ClTimeSlotsCount_Three,    /*!< Three*/
        NUM_CLTIMESLOTSCOUNT
    };

    enum CxpLinkConfigurationStatusEnums    /*!< This feature indicates the current and active Link configuration used by the Device.*/
    {
        CxpLinkConfigurationStatus_None,    /*!< The Link configuration of the Device is unknown. Either the configuration operation has failed or there is nothing connected.*/
        CxpLinkConfigurationStatus_Pending,    /*!< The Device is in the process of configuring the Link. The Link cannot be used yet.*/
        CxpLinkConfigurationStatus_CXP1_X1,    /*!< 1 Connection operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfigurationStatus_CXP2_X1,    /*!< 1 Connection operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfigurationStatus_CXP3_X1,    /*!< 1 Connection operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfigurationStatus_CXP5_X1,    /*!< 1 Connection operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfigurationStatus_CXP6_X1,    /*!< 1 Connection operating at CXP-6 speed (6.25 Gbps).*/
        CxpLinkConfigurationStatus_CXP1_X2,    /*!< 2 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfigurationStatus_CXP2_X2,    /*!< 2 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfigurationStatus_CXP3_X2,    /*!< 2 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfigurationStatus_CXP5_X2,    /*!< 2 Connections operating at CXP-4 speed (5.00 Gbps).*/
        CxpLinkConfigurationStatus_CXP6_X2,    /*!< 3 Connections operating at CXP-5 speed (6.25 Gbps).*/
        CxpLinkConfigurationStatus_CXP1_X3,    /*!< 3 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfigurationStatus_CXP2_X3,    /*!< 3 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfigurationStatus_CXP3_X3,    /*!< 3 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfigurationStatus_CXP5_X3,    /*!< 3 Connections operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfigurationStatus_CXP6_X3,    /*!< 3 Connections operating at CXP-6 speed (6.25 Gbps).*/
        CxpLinkConfigurationStatus_CXP1_X4,    /*!< 4 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfigurationStatus_CXP2_X4,    /*!< 4 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfigurationStatus_CXP3_X4,    /*!< 4 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfigurationStatus_CXP5_X4,    /*!< 4 Connections operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfigurationStatus_CXP6_X4,    /*!< 4 Connections operating at CXP-6 speed (6.25 Gbps).*/
        CxpLinkConfigurationStatus_CXP1_X5,    /*!< 5 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfigurationStatus_CXP2_X5,    /*!< 5 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfigurationStatus_CXP3_X5,    /*!< 5 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfigurationStatus_CXP5_X5,    /*!< 5 Connections operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfigurationStatus_CXP6_X5,    /*!< 5 Connections operating at CXP-6 speed (6.25 Gbps).*/
        CxpLinkConfigurationStatus_CXP1_X6,    /*!< 6 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfigurationStatus_CXP2_X6,    /*!< 6 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfigurationStatus_CXP3_X6,    /*!< 6 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfigurationStatus_CXP5_X6,    /*!< 6 Connections operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfigurationStatus_CXP6_X6,    /*!< 6 Connections operating at CXP-6 speed (6.25 Gbps).*/
        NUM_CXPLINKCONFIGURATIONSTATUS
    };

    enum CxpLinkConfigurationPreferredEnums    /*!< Provides the Link configuration that allows the Transmitter Device to operate in its default mode.*/
    {
        CxpLinkConfigurationPreferred_CXP1_X1,    /*!< 1 Connection operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfigurationPreferred_CXP2_X1,    /*!< 1 Connection operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfigurationPreferred_CXP3_X1,    /*!< 1 Connection operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfigurationPreferred_CXP5_X1,    /*!< 1 Connection operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfigurationPreferred_CXP6_X1,    /*!< 1 Connection operating at CXP-6 speed (6.25 Gbps).*/
        CxpLinkConfigurationPreferred_CXP1_X2,    /*!< 2 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfigurationPreferred_CXP2_X2,    /*!< 2 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfigurationPreferred_CXP3_X2,    /*!< 2 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfigurationPreferred_CXP5_X2,    /*!< 2 Connections operating at CXP-4 speed (5.00 Gbps).*/
        CxpLinkConfigurationPreferred_CXP6_X2,    /*!< 3 Connections operating at CXP-5 speed (6.25 Gbps).*/
        CxpLinkConfigurationPreferred_CXP1_X3,    /*!< 3 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfigurationPreferred_CXP2_X3,    /*!< 3 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfigurationPreferred_CXP3_X3,    /*!< 3 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfigurationPreferred_CXP5_X3,    /*!< 3 Connections operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfigurationPreferred_CXP6_X3,    /*!< 3 Connections operating at CXP-6 speed (6.25 Gbps).*/
        CxpLinkConfigurationPreferred_CXP1_X4,    /*!< 4 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfigurationPreferred_CXP2_X4,    /*!< 4 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfigurationPreferred_CXP3_X4,    /*!< 4 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfigurationPreferred_CXP5_X4,    /*!< 4 Connections operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfigurationPreferred_CXP6_X4,    /*!< 4 Connections operating at CXP-6 speed (6.25 Gbps).*/
        CxpLinkConfigurationPreferred_CXP1_X5,    /*!< 5 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfigurationPreferred_CXP2_X5,    /*!< 5 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfigurationPreferred_CXP3_X5,    /*!< 5 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfigurationPreferred_CXP5_X5,    /*!< 5 Connections operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfigurationPreferred_CXP6_X5,    /*!< 5 Connections operating at CXP-6 speed (6.25 Gbps).*/
        CxpLinkConfigurationPreferred_CXP1_X6,    /*!< 6 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfigurationPreferred_CXP2_X6,    /*!< 6 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfigurationPreferred_CXP3_X6,    /*!< 6 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfigurationPreferred_CXP5_X6,    /*!< 6 Connections operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfigurationPreferred_CXP6_X6,    /*!< 6 Connections operating at CXP-6 speed (6.25 Gbps).*/
        NUM_CXPLINKCONFIGURATIONPREFERRED
    };

    enum CxpLinkConfigurationEnums    /*!< This feature allows specifying the Link configuration for the communication between the Receiver and Transmitter Device. In most cases this feature does not need to be written because automatic discovery will set configuration correctly to the value returned by CxpLinkConfigurationPreferred. Note that the currently active configuration of the Link can be read using CxpLinkConfigurationStatus.*/
    {
        CxpLinkConfiguration_Auto,    /*!< Sets Automatic discovery for the Link Configuration.*/
        CxpLinkConfiguration_CXP1_X1,    /*!< Force the Link to 1 Connection operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfiguration_CXP2_X1,    /*!< Force the Link to 1 Connection operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfiguration_CXP3_X1,    /*!< Force the Link to 1 Connection operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfiguration_CXP5_X1,    /*!< Force the Link to 1 Connection operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfiguration_CXP6_X1,    /*!< Force the Link to 1 Connection operating at CXP-6 speed (6.25 Gbps).*/
        CxpLinkConfiguration_CXP1_X2,    /*!< Force the Link to 2 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfiguration_CXP2_X2,    /*!< Force the Link to 2 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfiguration_CXP3_X2,    /*!< Force the Link to 2 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfiguration_CXP5_X2,    /*!< Force the Link to 2 Connections operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfiguration_CXP6_X2,    /*!< Force the Link to 3 Connections operating at CXP-6 speed (6.25 Gbps).*/
        CxpLinkConfiguration_CXP1_X3,    /*!< Force the Link to 3 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfiguration_CXP2_X3,    /*!< Force the Link to 3 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfiguration_CXP3_X3,    /*!< Force the Link to 3 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfiguration_CXP5_X3,    /*!< Force the Link to 3 Connections operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfiguration_CXP6_X3,    /*!< Force the Link to 3 Connections operating at CXP-6 speed (6.25 Gbps).*/
        CxpLinkConfiguration_CXP1_X4,    /*!< Force the Link to 4 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfiguration_CXP2_X4,    /*!< Force the Link to 4 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfiguration_CXP3_X4,    /*!< Force the Link to 4 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfiguration_CXP5_X4,    /*!< Force the Link to 4 Connections operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfiguration_CXP6_X4,    /*!< Force the Link to 4 Connections operating at CXP-6 speed (6.25 Gbps).*/
        CxpLinkConfiguration_CXP1_X5,    /*!< Force the Link to 5 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfiguration_CXP2_X5,    /*!< Force the Link to 5 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfiguration_CXP3_X5,    /*!< Force the Link to 5 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfiguration_CXP5_X5,    /*!< Force the Link to 5 Connections operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfiguration_CXP6_X5,    /*!< Force the Link to 5 Connections operating at CXP-6 speed (6.25 Gbps).*/
        CxpLinkConfiguration_CXP1_X6,    /*!< Force the Link to 6 Connections operating at CXP-1 speed (1.25 Gbps).*/
        CxpLinkConfiguration_CXP2_X6,    /*!< Force the Link to 6 Connections operating at CXP-2 speed (2.50 Gbps).*/
        CxpLinkConfiguration_CXP3_X6,    /*!< Force the Link to 6 Connections operating at CXP-3 speed (3.125 Gbps).*/
        CxpLinkConfiguration_CXP5_X6,    /*!< Force the Link to 6 Connections operating at CXP-5 speed (5.00 Gbps).*/
        CxpLinkConfiguration_CXP6_X6,    /*!< Force the Link to 6 Connections operating at CXP-6 speed (6.25 Gbps).*/
        NUM_CXPLINKCONFIGURATION
    };

    enum CxpConnectionTestModeEnums    /*!< Enables the test mode for an individual physical connection of the Device.*/
    {
        CxpConnectionTestMode_Off,    /*!< Off*/
        CxpConnectionTestMode_Mode1,    /*!< Mode 1*/
        NUM_CXPCONNECTIONTESTMODE
    };

    enum CxpPoCxpStatusEnums    /*!< Returns the Power over CoaXPress (PoCXP) status of the Device.*/
    {
        CxpPoCxpStatus_Auto,    /*!< Normal automatic PoCXP operation.*/
        CxpPoCxpStatus_Off,    /*!< PoCXP is forced off.*/
        CxpPoCxpStatus_Tripped,    /*!< The Link has shut down because of an over-current trip.*/
        NUM_CXPPOCXPSTATUS
    };

    /*@}*/

    /*@}*/

}
#endif // FLIR_SPINNAKER_CAMERA_DEFS_H