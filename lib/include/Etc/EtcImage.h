/*
 * Copyright 2015 The Etc2Comp Authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

// Shared Lib Support
#include "Etc/Etc_export.h"

#include "Etc/EtcColorFloatRGBA.h"
#include "Etc/EtcBlock4x4EncodingBits.h"
#include "Etc/EtcErrorMetric.h"

namespace Etc
{
	class Block4x4;
	class EncoderSpec;
	
    class ETC_EXPORT Image
    {
    public:

		enum  EncodingStatus
		{
			SUCCESS = 0,
		};
		
		enum class Format
		{
			UNKNOWN,
			//
			ETC1,
			//
			// ETC2 formats
			RGB8,
			SRGB8,
			RGBA8,
			SRGBA8,
			
            R11,
			SIGNED_R11,
			RG11,
			SIGNED_RG11,
            
			RGB8A1,
			SRGB8A1,
			//
			FORMATS,
			//
			DEFAULT = SRGB8
		};

        /* COMPARED TO ORIGINAL
         * - Added 'Format a_format' arg
         */
		// constructor using source image
		Image(Format a_format, const ColorR8G8B8A8 *a_pafSourceRGBA,
                unsigned int a_uiSourceWidth, unsigned int a_uiSourceHeight,
				ErrorMetric a_errormetric);

		// constructor using encoding bits
//		Image(Format a_format, 
//				unsigned int a_uiSourceWidth, unsigned int a_uiSourceHeight,
//				unsigned char *a_paucEncidingBits, unsigned int a_uiEncodingBitsBytes,
//				//Image *a_pimageSource,
//				ErrorMetric a_errormetric);

		~Image(void);


        /* COMPARED TO ORIGINAL
         * - Missing 'Format a_format' arg (moved to ctor)
         * - Missing 'ErrorMetric a_errormetric' arg
         * - Missing 'unsigned int a_uiJobs'
         * - Missing 'unsigned int a_uiMaxJobs' arg
         * - Added 'float blockPercent'
         * - Added 'uint8_t* outputTexture'
         */
        // Multipass encoding.  Uses tons of memory but can thread even though it doesn't help.
		EncodingStatus Encode(float blockPercent, float a_fEffort, uint8_t* outputTexture);

        // Single-pass encoding. One block at a time to not was so much memory and time as Encode does.
        EncodingStatus EncodeSinglepass(float a_fEffort, uint8_t* outputTexture);
        
        // Translate to rgba8unorm texture (even r/rg11)
        EncodingStatus Decode(const uint8_t* etcBlocks, uint8_t* outputTexture);
       
		inline void AddToEncodingStatus(EncodingStatus a_encStatus)
		{
			m_encodingStatus = (EncodingStatus)((unsigned int)m_encodingStatus | (unsigned int)a_encStatus);
		}
		
		inline unsigned int GetSourceWidth(void) const
		{
			return m_uiSourceWidth;
		}

		inline unsigned int GetSourceHeight(void) const
		{
			return m_uiSourceHeight;
		}

        inline unsigned int GetNumberOfBlockColumns() const
        {
            return m_uiBlockColumns;
        }
        inline unsigned int GetNumberOfBlockRows() const
        {
            return m_uiBlockRows;
        }

		inline unsigned int GetNumberOfBlocks() const
		{
			return m_uiBlockColumns * m_uiBlockRows;
		}

        inline unsigned int GetBlockSize() const
        {
            return m_uiBlockSize;
        }
        
        inline unsigned char * GetEncodingBits(void)
		{
			return m_paucEncodingBits;
		}

		inline unsigned int GetEncodingBitsBytes(void)
		{
			return m_uiEncodingBitsBytes;
		}

		inline int GetEncodingTimeMs(void) const
		{
			return m_iEncodeTime_ms;
		}

		float GetError(void) const;

        inline bool HasSourcePixels() const
        {
            return m_pafrgbaSource != nullptr;
        }
        
		inline ColorFloatRGBA GetSourcePixel(unsigned int x, unsigned int y) const
		{
            // clamp on border instead of returning nullptr and NaNs.  Might weight color more.
			if (x >= m_uiSourceWidth)
			{
                x = m_uiSourceWidth - 1;
			}
            if (y >= m_uiSourceHeight)
            {
                y = m_uiSourceHeight - 1;
            }

            // Convert to float pixel here.  This keeps input image much smaller.  Only 8-bit data.
            // But can't encode to R11 or R11G11 with full fp32 inputs.
			return ColorFloatRGBA::ConvertFromRGBA8(m_pafrgbaSource[y * m_uiSourceWidth + x]);
		}

		inline Format GetFormat(void) const
		{
			return m_format;
		}

		static Block4x4EncodingBits::Format DetermineEncodingBitsFormat(Format a_format);

		inline static unsigned short CalcExtendedDimension(unsigned short a_ushOriginalDimension)
		{
			return (unsigned short)((a_ushOriginalDimension + 3) & ~3);
		}

		inline ErrorMetric GetErrorMetric(void) const
		{
			return m_errormetric;
		}

		static const char * EncodingFormatToString(Image::Format a_format);
        
		const char * EncodingFormatToString(void) const;
		
    private:
		//Image(void);
		
		// inputs
		const ColorR8G8B8A8 *m_pafrgbaSource;
		unsigned int m_uiSourceWidth;
		unsigned int m_uiSourceHeight;
		unsigned int m_uiBlockColumns;
		unsigned int m_uiBlockRows;
		
        // encoding
		Format m_format;
		Block4x4EncodingBits::Format m_encodingbitsformat;
        unsigned int m_uiBlockSize; // depends on format
		unsigned int m_uiEncodingBitsBytes;		// for entire image
		unsigned char *m_paucEncodingBits;
		ErrorMetric m_errormetric;
		float m_fEffort;
        
		// stats
		int m_iEncodeTime_ms;
		
		//this will hold any warning or errors that happen during encoding
		EncodingStatus m_encodingStatus;
	};

} // namespace Etc
