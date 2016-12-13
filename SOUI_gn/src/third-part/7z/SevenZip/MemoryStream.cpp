/********************************************************************
  Created Date: 2008-09-05
  Author: wuding
  Version: 1.0
  Last Version Date:
  Version Date:
  Modified History:
  version Date      Author    Description
  2008-11-11        wuding    
  2012-12-13        modify to support image only	
********************************************************************/

#include "MemoryStream.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>
#include <string>

static std::string ConvertWStringToString(const wchar_t* pStr, int len, unsigned int CodePage)
{
	std::string buf;

	if (pStr == NULL)
	{
		return buf;
	}

	if (len < 0 && len != -1)
	{
		return buf;
	}

	// figure out how many narrow characters we are going to get
	int nChars = WideCharToMultiByte(CodePage, 0,
		pStr, len, NULL, 0, NULL, NULL);
	if (len == -1)
		--nChars;
	if (nChars == 0)
		return "";

	// convert the wide string to a narrow string
	// nb: slightly naughty to write directly into the string like this
	buf.resize(nChars);
	WideCharToMultiByte(CodePage, 0, pStr, len,
		const_cast<char*>(buf.c_str()), nChars, NULL, NULL);

	return buf;
}


MemoryStream::MemoryStream()
{
       Reset();
}

MemoryStream::~MemoryStream()
{
	  Clear();
}

void MemoryStream::Reset()
{
	  m_lBlobLen   = 0;
	  m_BlobPtr    = m_MemoryStream;
      m_lBufferLen = BLOB_BUFFER_BLOCK_SIZE;

      ResetRead();
}

//清空所有数据,并释放内存
void MemoryStream::Clear()
{
	//如果缓冲区大小大于最小缓冲，则表明已经在堆上分配空间了，则要释放堆上面的空间
	if( m_lBufferLen>BLOB_BUFFER_BLOCK_SIZE)
	{
         free(m_BlobPtr); 
	}
    Reset(); 
}

//清空所有数据,不释放内存
void MemoryStream::ClearContent()
{
	m_lBlobLen = 0;
	ResetRead();
}

void MemoryStream::ResetRead()
{
    m_ReadLen    = 0;
} 

const unsigned char *MemoryStream::GetBlobPtr()
{
	return (m_BlobPtr);
}


unsigned char *MemoryStream::GetBlobRealPtr()
{
  return (m_BlobPtr);
}


unsigned long MemoryStream::GetBlobLength() const
{
	return(m_lBlobLen);
}

unsigned long MemoryStream::GetMemoryStreamLength()
{
  return(m_lBufferLen);
}
 
void MemoryStream::AllocBuffer(unsigned long nBufSize)
{
	if (nBufSize > this->GetMemoryStreamLength())
	{
		IncreaseBufferSize(nBufSize - this->GetMemoryStreamLength(), false);
		m_lBlobLen = nBufSize;
	}
	else
	{
		m_lBlobLen = nBufSize;
	}
}

//将缓冲区扩大到nIncreaseSize,bCopyOldData表示，分配新的空间后，旧的数据要不拷贝到新空间上 
void MemoryStream::IncreaseBufferSize(unsigned long nIncreaseSize, bool bCopyOldData)
{
	unsigned char *temp_Buffer;
    unsigned long lMallocSize;

	//如果总的分配空间比栈小，则无需分配
	if(BLOB_BUFFER_BLOCK_SIZE> m_lBlobLen+nIncreaseSize)
	      return;

    //如果要分配的空间大小加上实际大小 比现有的缓冲小，则无需分配
	if(m_lBufferLen> m_lBlobLen+nIncreaseSize)
      return;


	nIncreaseSize = (nIncreaseSize<BLOB_BUFFER_BLOCK_SIZE)? BLOB_BUFFER_BLOCK_SIZE:nIncreaseSize;


	unsigned long incr_size = m_lBufferLen + nIncreaseSize;
	if (m_lBufferLen * 2 > incr_size)
	{
		incr_size = m_lBufferLen * 2;
	}

	lMallocSize = incr_size;

	temp_Buffer = (unsigned char *)malloc(lMallocSize);
	if( temp_Buffer == NULL )
	{
			//如果超过标准栈缓冲大小，表明已经分配了堆空间了，则要释放堆空间
			if(m_lBufferLen>BLOB_BUFFER_BLOCK_SIZE)
				free(m_BlobPtr);
               
			Reset();
			return ;
	}

	//如果要拷贝旧数据到新的缓冲中去
   if (bCopyOldData && m_lBlobLen>0)
       memcpy(temp_Buffer,m_BlobPtr,m_lBlobLen);

    //如果m_lBufferLen大于BLOB_BUFFER_BLOCK_SIZE，表明已经在使用堆缓冲了，则要释放原有的堆缓冲
    if(m_lBufferLen>BLOB_BUFFER_BLOCK_SIZE)
      free(m_BlobPtr);

	m_BlobPtr  = temp_Buffer;
    m_lBufferLen = lMallocSize;
}

void MemoryStream::SetBlobContent(const unsigned char *BlobPtr,unsigned long nBlobLen)
{ 
      if(nBlobLen>0)
      {
		  //如果要增加的长度加上当前实际长度大于总缓冲大小的话
	      if(m_lBufferLen< m_lBlobLen+nBlobLen)
			  IncreaseBufferSize(nBlobLen, false);

		  ClearContent();
	      memcpy(m_BlobPtr,BlobPtr,nBlobLen);
	      m_lBlobLen = nBlobLen;
	  }
	  else
	      Clear();
}

void MemoryStream::AppendBlobContentChar(const unsigned char BlobChar)
{
	//如果要增加的长度加上当前实际长度大于总缓冲大小的话
	const int nBlobLen = 1;
	if (m_lBufferLen< m_lBlobLen + nBlobLen)
		IncreaseBufferSize(nBlobLen, false);
	char temp[1];
	temp[0] = BlobChar;
	memcpy(m_BlobPtr + m_lBlobLen, &temp, nBlobLen);
	m_lBlobLen += nBlobLen;
}

void MemoryStream::AppendBlobContent(const unsigned char *BlobPtr,unsigned long nBlobLen)
{
   if(nBlobLen>0)
   { 
			//如果要增加的长度加上当前实际长度大于总缓冲大小的话
			if(m_lBufferLen< m_lBlobLen+nBlobLen)
				IncreaseBufferSize(nBlobLen, true);

			memcpy(m_BlobPtr+m_lBlobLen,BlobPtr,nBlobLen);
			m_lBlobLen += nBlobLen;
   }
} 

bool MemoryStream::LoadBlobFromFile(const wchar_t *sFileName)
{
	std::string fileName = ConvertWStringToString(sFileName, (int)wcslen(sFileName), CP_ACP);
	return LoadBlobFromFile(fileName.c_str());
}

bool MemoryStream::SaveBlobToFile(const wchar_t *sFileName)
{
	std::string fileName = ConvertWStringToString(sFileName, (int)wcslen(sFileName), CP_ACP);
	return SaveBlobToFile(fileName.c_str());
}

bool MemoryStream::LoadBlobFromFile(const char *sFileName)
{
	FILE *fp;
	long nReadCnt;

	fp = fopen(sFileName,"rb");
	if(fp == NULL)
	{
		return false;
	}
    
	fseek(fp,0,SEEK_END);
	long file_size = ftell(fp);
  fseek(fp,0,SEEK_SET);

  Clear();
        
  IncreaseBufferSize(file_size, false);

	if(0 == m_BlobPtr )
	{
		fclose(fp);
		return false;
	}

	nReadCnt = (long)fread(m_BlobPtr, 1, file_size, fp);
	if( nReadCnt<file_size )
	{
           if(ferror(fp))
	       {
              Clear(); 
			  return false;
		   }
    }

    m_lBlobLen = file_size;
	fclose(fp);
	return true;
}

bool MemoryStream::SaveBlobToFile(const char *sFileName)
{
	FILE *fp;
	unsigned long WCnt;

	fp = fopen(sFileName,"wb");
	if(fp==NULL)
	{ 
		return false;
	}

	WCnt = (long)fwrite( m_BlobPtr,1,m_lBlobLen, fp );
	if(WCnt<m_lBlobLen)
	{
		fclose(fp); 
		return false;
	}
	fclose(fp);
	return true;
}