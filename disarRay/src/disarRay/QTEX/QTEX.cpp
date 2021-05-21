#include "drpch.h"
#include "QTEX.h"

namespace Dray
{
	QTEX::QTEX(u32 width, u32 height, u32 pixelSize)
	{
		m_DataSize = ((u64)width * (u64)height * (u64)pixelSize) + 16;
		m_Data = interc(u8*, malloc(m_DataSize));

		if (m_Data == nullptr)
		{
			m_FailMask = DRAY_FAILMASK_INSUFFICIENT_MEMORY;
		}
		else
		{
			SetSignature(0x51544558);
			SetWidth(width);
			SetHeight(height);
			SetPixelSize(pixelSize);
		}
	}

	QTEX::QTEX(str8 filepath)
	{
		DRAY_TRACE("Working directory: {2}", std::filesystem::current_path());
		std::ifstream file(filepath, std::ifstream::in | std::ifstream::binary);

		if (file.is_open())
		{
			m_DataSize = std::filesystem::file_size(filepath);
			m_Data = interc(u8*, malloc(m_DataSize));

			if (m_Data == nullptr)
			{
				m_FailMask = DRAY_FAILMASK_INSUFFICIENT_MEMORY;
				DRAY_DYN_ERROR("Insufficient memory to allocate for file {2}.", filepath);
				return;
			}

			file.seekg(0, std::ios::beg);
			file.read(interc(char*, m_Data), m_DataSize);
			file.close();

			if (GetSignature() != 0x51544558)
			{
				m_FailMask = DRAY_FAILMASK_INVALID_FILE;
				DRAY_DYN_ERROR("File {2} failed at signature check.", filepath);
				return;
			}
			if ((m_DataSize - 16) != GetBufferSize())
			{
				m_FailMask = DRAY_FAILMASK_INVALID_FILE;
				DRAY_DYN_ERROR("File {2} failed at color buffer check.", filepath);
				return;
			}
		}
		else
		{
			m_FailMask = DRAY_FAILMASK_COULD_NOT_OPEN_FILE;
			DRAY_DYN_ERROR("File {2} could not be opened.", filepath);
			return;
		}
		if (m_FailMask == DRAY_FAILMASK_SUCCESS)
		{
			DRAY_DYN_INFO("File {2} loaded into QTEX successfully!!! :D", filepath);
		}
	}

	QTEX::~QTEX()
	{
		if((m_FailMask & DRAY_FAILMASK_INSUFFICIENT_MEMORY) == DRAY_FAILMASK_SUCCESS)
			free(m_Data);
	}

	void QTEX::Save(str8 filepath)
	{
		std::ofstream file(filepath, std::ofstream::out | std::ofstream::binary);

		if (m_FailMask != DRAY_FAILMASK_SUCCESS)
		{
			DRAY_DYN_ERROR("QTEX {2} is not valid, cannot write to file.", filepath);
			return;
		}

		if (file.is_open())
		{
			file.seekp(0, std::ofstream::beg);
			file.write(interc(char*, m_Data), m_DataSize);
			file.close();

			DRAY_DYN_INFO("QTEX written into file {2} successfully!!! :D", filepath);
		}
		else
		{
			DRAY_DYN_ERROR("Error writting to file {2}.", filepath);
		}
	}
}
