#pragma once

#include "DrayIntern.h"

namespace Dray
{
	class DRAY_API QTEX
	{
	public:
		QTEX() {};
		QTEX(u32 width, u32 height, u32 pixelSize = 4);
		QTEX(str8 filepath);
		~QTEX();

		void Save(str8 filepath);

		u64 GetDataSize()	const { return m_DataSize;									}
		u8  GetFailMask()	const { return m_FailMask;									}
		u32 GetSignature()	const { return DRAY_SWAP_32(*interc(u32*, m_Data +  0));	}
		u32 GetWidth()		const { return DRAY_SWAP_32(*interc(u32*, m_Data +  4));	}
		u32 GetHeight()		const { return DRAY_SWAP_32(*interc(u32*, m_Data +  8));	}
		u32 GetPixelSize()	const { return DRAY_SWAP_32(*interc(u32*, m_Data + 12));	}
		u8* GetBuffer()		const { return interc(u8*,  m_Data + 16);					}
		u32 GetBufferSize() const { return GetWidth() * GetHeight() * GetPixelSize();	}

	private:
		DRAY_FAILMASK m_FailMask = DRAY_FAILMASK_SUCCESS;
		u64 m_DataSize;
		u8* m_Data;

		void SetSignature(u32 v)	const { interc(u32*, m_Data)[0] = DRAY_SWAP_32(v); }
		void SetWidth(u32 v)		const { interc(u32*, m_Data)[1] = DRAY_SWAP_32(v); }
		void SetHeight(u32 v)		const { interc(u32*, m_Data)[2] = DRAY_SWAP_32(v); }
		void SetPixelSize(u32 v)	const { interc(u32*, m_Data)[3] = DRAY_SWAP_32(v); }
	};
}
