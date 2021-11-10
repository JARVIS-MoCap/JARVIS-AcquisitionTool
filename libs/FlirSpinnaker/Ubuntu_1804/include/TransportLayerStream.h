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

#ifndef FLIR_SPINNAKER_TRANSPORTLAYERSTREAM_H
#define FLIR_SPINNAKER_TRANSPORTLAYERSTREAM_H

#include "SpinnakerPlatform.h"
#include "SpinGenApi/SpinnakerGenApi.h"
#include "TransportLayerDefs.h"
#include <string>

namespace Spinnaker
{
	/**
	* @defgroup SpinnakerQuickSpinClasses Spinnaker QuickSpin Classes
	*/
	/*@{*/

	/**
	* @defgroup TransportLayerStream_h TransportLayerStream Class
	*/
	/*@{*/

	/**
	*@brief Part of the QuickSpin API to provide access to camera information without having to first initialize the camera.
	*/

	class SPINNAKER_API TransportLayerStream
	{
	public:
		TransportLayerStream(GenApi::INodeMap *nodeMapTLDevice);
		~TransportLayerStream();

	protected:
		TransportLayerStream();

	private:
		TransportLayerStream(const TransportLayerStream&);
		TransportLayerStream& operator=(const TransportLayerStream&);
		TransportLayerStream& operator=(GenApi::INodeMap &);

	public:
		/**
		 * Description: Device unique ID for the data stream, e.g. a GUID.
		 * Visibility: Expert
		 */
		GenApi::IString &StreamID;

		/**
		 * Description: Stream type of the device.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<StreamTypeEnum> &StreamType;

		/**
		 * Description: Controls the number of buffers to be used on this stream upon acquisition start when in manual mode.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamBufferCountManual;

		/**
		 * Description: Displays the number of buffers to be used on this stream upon acquisition start. Recalculated on acquisition start if in auto mode.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamBufferCountResult;

		/**
		 * Description: Controls the maximum number of buffers that should be used on this stream. This value is calculated based on the available system memory.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamBufferCountMax;

		/**
		 * Description: Controls access to setting the number of buffers used for the stream. Locked to Manual mode on 32-bit Windows due to memory constraints.
		 * Visibility: Expert
		 */
		GenApi::IEnumerationT<StreamBufferCountModeEnum> &StreamBufferCountMode;

		/**
		 * Description: Available buffer handling modes of this data stream:
		 * Visibility: Beginner
		 */
		GenApi::IEnumerationT<StreamBufferHandlingModeEnum> &StreamBufferHandlingMode;

		/**
		 * Description: Minimal number of buffers to announce to enable selected buffer handling mode.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamAnnounceBufferMinimum;

		/**
		 * Description: Number of announced (known) buffers on this stream. This value is volatile. It may change if additional buffers are announced and/or buffers are revoked by the GenTL Consumer.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamAnnouncedBufferCount;

		/**
		 * Description: Number of frames started in the acquisition engine. This number is incremented every time in case of a new buffer is started and then to be filled (data written to) regardless even if the buffer is later delivered to the user or discarded for any reason. This number is initialized with 0 at at the time of the stream is opened. It is not reset until the stream is closed.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamStartedFrameCount;

		/**
		 * Description: Number of delivered frames since last acquisition start. It is not reset until the stream is closed.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamDeliveredFrameCount;

		/**
		 * Description: Number of lost frames due to queue underrun. This number is initialized with zero at the time the stream is opened and incremented every time the data could not be acquired because there was no buffer in the input buffer pool. It is not reset until the stream is closed.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamLostFrameCount;

		/**
		 * Description: Number of buffers in the input buffer pool plus the buffers(s) currently being filled.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamInputBufferCount;

		/**
		 * Description: Number of buffers in the output buffer queue.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamOutputBufferCount;

		/**
		 * Description: Enables or disables CRC checks on received images.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &StreamCRCCheckEnable;

		/**
		 * Description: Enables or disables the packet resend mechanism.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &GevPacketResendMode;

		/**
		 * Description: Maximum number of resend requests per image. Each resend request consists of a span of consecutive packet IDs.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevMaximumNumberResendRequests;

		/**
		 * Description: Time in milliseconds to wait after the image trailer is received and before the image is completed by the driver.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevPacketResendTimeout;

		/**
		 * Description: Flag indicating whether the acquisition engine is started or not.
		 * Visibility: Expert
		 */
		GenApi::IBoolean &StreamIsGrabbing;

		/**
		 * Description: Maximum number of chunks to be expected in a buffer.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamChunkCountMaximum;

		/**
		 * Description: Alignment size in bytes of the buffer passed to DSAnnounceBuffer.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamBufferAlignment;

		/**
		 * Description: Displays number of packets received on this stream.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevTotalPacketCount;

		/**
		 * Description: Displays number of packets missed on this stream.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevFailedPacketCount;

		/**
		 * Description: Displays number of packets received after retransmit request on this stream.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevResendPacketCount;

		/**
		 * Description: Displays number of incomplete images with missing leader/trailer information.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamFailedBufferCount;

		/**
		 * Description: Displays number of packets requested to be retransmitted on this stream.
		 * Visibility: Expert
		 */
		GenApi::IInteger &GevResendRequestCount;

		/**
		 * Description: Controls the image breakup size that should be used on this stream.
		 * Visibility: Expert
		 */
		GenApi::IInteger &StreamBlockTransferSize;


	protected:
		friend class CameraBase;
		friend class ICameraBase;
		friend class CameraInternal;

	};
	/*@}*/

	/*@}*/

}
#endif // FLIR_SPINNAKER_TRANSPORTLAYERSTREAM_H