//=============================================================================
// Copyright (c) 2001-2019 FLIR Systems, Inc. All Rights Reserved.
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

#ifndef SPINNAKER_GENAPI_FILESTREAM_H_
#define SPINNAKER_GENAPI_FILESTREAM_H_

#include "GCString.h"
#include "GCUtilities.h"

#include "SpinnakerPlatform.h"

#if (__GNUC__)
#include <unistd.h>
#endif

namespace Spinnaker
{
    namespace GenApi
    {

        struct INodeMap;

        /**
         *  @defgroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @defgroup Filestream_h Filestream Class
         */
        /*@{*/

        /**
         * @brief
         * Adapter between the std::iostreambuf and the SFNC Features representing the device file system
         *
         * The adapter assumes, that the features provide stdio file access
         * compatible semantic
         *
         */
        class SPINNAKER_API FileProtocolAdapter
        {
          public:
            /**
             * @brief
             * Constructor
             *
             */
            FileProtocolAdapter();
            virtual ~FileProtocolAdapter();

            /**
             * @brief
             * attach file protocol adapter to NodeMap
             *
             * @param pInterface
             * NodeMap of the device to which the FileProtocolAdapter is attached
             *
             * @return true if attach was successful, false if not
             *
             */
            bool attach(::Spinnaker::GenApi::INodeMap* pInterface);

            /**
             * @brief
             * open a file on the device
             *
             * @param pFileName
             * filename of the file to open. The filename must exist in the Enumeration FileSelector
             *
             * @param mode
             * mode to open the file. The mode must exist in the Enumeration FileOpenMode
             *
             * @returns
             * true on success, false on error
             *
             */
            bool openFile(const char* pFileName, std::ios_base::openmode mode);

            /**
             * @brief
             * close a file on the device
             *
             * @param pFileName
             * filename of the file to open. The filename must exist in the Enumeration FileSelector
             *
             * @returns
             * true on success, false on error
             */
            bool closeFile(const char* pFileName);

            /**
             * @brief
             * writes data into a file.
             *
             * @param buf
             * source buffer
             *
             * @param offs
             * offset into the device file
             *
             * @param len
             * count of bytes to write
             *
             * @param pFileName
             * filename of the file to write into The filename must exist in the Enumeration FileSelector
             *
             * @returns
             * count of bytes written
             *
             */
            std::streamsize write(const char* buf, int64_t offs, int64_t len, const char* pFileName);

            /**
             * @brief
             * read data from the device into a buffer
             *
             * @param buf
             * target buffer
             *
             * @param offs
             * offset in the device file to read from
             *
             * @param len
             * count of bytes to read
             *
             * @param pFileName
             * filename of the file to write into The filename must exist in the Enumeration FileSelector
             *
             * @returns
             * count of bytes successfully read
             *
             */
            std::streamsize read(char* buf, int64_t offs, std::streamsize len, const char* pFileName);

            /**
             * @brief
             * fetch max FileAccessBuffer length for a file
             *
             * @param pFileName
             * filename of the file to open. The filename must exist in the Enumeration FileSelector
             *
             * @param mode
             * mode to open the file. The mode must exist in the Enumeration FileOpenMode
             *
             * @returns
             * max length of FileAccessBuffer in the given mode on the given file
             *
             */
            int64_t getBufSize(const char* pFileName, std::ios_base::openmode mode);

            /**
             * @brief
             * Delete the content of the file.
             *
             * @param pFileName
             * filename of the file to open. The filename must exist in the Enumeration FileSelector
             *
             * @returns
             * true on success, false on error
             */
            bool deleteFile(const char* pFileName);

          private:
            void* m_fileProtocolAdapter;
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup Filestream_h Filestream Class
         */
        /*@{*/

        template <typename CharType, typename Traits>
        class IDevFileStreamBuf : public std::basic_streambuf<CharType, Traits>
        {

            typedef Traits traits_type;
            typedef typename Traits::int_type int_type;
            typedef typename Traits::char_type char_type;
            typedef IDevFileStreamBuf<CharType, Traits> filebuf_type;

            // GET next ptr
            using std::basic_streambuf<CharType, Traits>::gptr;
            // GET end ptr
            using std::basic_streambuf<CharType, Traits>::egptr;
            // GET begin ptr
            using std::basic_streambuf<CharType, Traits>::eback;
            // increment next pointer
            using std::basic_streambuf<CharType, Traits>::gbump;
            // set buffer info
            using std::basic_streambuf<CharType, Traits>::setg;

          public:
            IDevFileStreamBuf()
                : m_pBuffer(0), m_BufSize(0), m_pAdapter(0),
                  m_fpos(0){
                      // This already handled by the base class constructor, right?
                      // std::basic_streambuf<CharType, Traits>::_Init();
                  };

            ~IDevFileStreamBuf()
            {
                // catch and dump all exceptions - we're in a destructor...
                try
                {
                    this->close();
                }
                catch (...)
                {
                }
            }

            filebuf_type* open(
                Spinnaker::GenApi::INodeMap* pInterface,
                const char* pFileName,
                std::ios_base::openmode mode = std::ios_base::in)
            {
                // get file protocol adapter
                m_pAdapter = new FileProtocolAdapter();

                // open file via Adapter
                if (!m_pAdapter || !m_pAdapter->attach(pInterface))
                {
                    delete m_pAdapter;
                    m_pAdapter = 0;
                    return 0;
                }

                // open file via Adapter
                if (!(m_pAdapter->openFile(pFileName, mode)))
                {
                    delete m_pAdapter;
                    m_pAdapter = 0;
                    return 0;
                }

                m_file = pFileName;
                // allocate buffer according to file info
                m_BufSize = (std::streamsize)m_pAdapter->getBufSize(m_file.c_str(), mode);
                m_pBuffer = new char_type[m_BufSize / sizeof(char_type)];

                // setg(buffer+pbSize, buffer+pbSize, buffer+pbSize);
                setg(m_pBuffer, m_pBuffer + m_BufSize, m_pBuffer + m_BufSize);

#ifdef _MSC_VER
                // is this reasonable?
                std::basic_streambuf<CharType, Traits>::_Init();
#endif

                return this;
            }

            bool is_open() const
            {
                return m_pAdapter != 0;
            }

            filebuf_type* close()
            {
                filebuf_type* ret = 0;
                if (this->is_open())
                {
                    // close file
                    if (m_pAdapter->closeFile(m_file.c_str()))
                    {
                        // no error
                        ret = this;
                    }
                    delete m_pAdapter;
                    m_pAdapter = 0;
                    // buffer
                    delete[] m_pBuffer;
                    m_pBuffer = 0;
                }
                return ret;
            }

          protected:
            int_type underflow()
            {
                if (gptr() < egptr())
                    return traits_type::to_int_type(*gptr());

                if (buffer_in() < 0)
                    return traits_type::eof();
                else
                    return traits_type::to_int_type(*gptr());
            }

            int_type pbackfail(int_type c)
            {
                if (gptr() != eback() || eback() < gptr())
                {
                    gbump(-1);
                    if (!traits_type::eq_int_type(c, traits_type::eof()))
                        *(gptr()) = static_cast<char_type>(traits_type::not_eof(c));
                    return traits_type::not_eof(c);
                }
                else
                    return traits_type::eof();
            }

          private:
            char_type* m_pBuffer;
            std::streamsize m_BufSize;

            GenICam::gcstring m_file;
            FileProtocolAdapter* m_pAdapter;
            int64_t m_fpos;

            int buffer_in()
            {

                std::streamsize retval = m_pAdapter->read(m_pBuffer, m_fpos, m_BufSize, m_file.c_str());

                if (retval <= 0)
                {
                    setg(0, 0, 0);
                    return -1;
                }
                else
                {
                    setg(m_pBuffer, m_pBuffer, m_pBuffer + retval);
                    m_fpos += retval;
                    return static_cast<int>(retval);
                }
            }

            // prohibit copying and assignment
            IDevFileStreamBuf(const IDevFileStreamBuf&);
            IDevFileStreamBuf& operator=(const IDevFileStreamBuf&);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup Filestream_h Filestream Class
         */
        /*@{*/

        template <typename CharType, typename Traits>
        class ODevFileStreamBuf : public std::basic_streambuf<CharType, Traits>
        {
            typedef Traits traits_type;

            typedef typename Traits::int_type int_type;
            typedef typename Traits::char_type char_type;
            typedef typename Traits::pos_type pos_type;
            typedef typename Traits::off_type off_type;

            typedef ODevFileStreamBuf<CharType, Traits> filebuf_type;

            // PUT begin
            using std::basic_streambuf<CharType, Traits>::pbase;
            // PUT next
            using std::basic_streambuf<CharType, Traits>::pptr;
            // PUT end
            using std::basic_streambuf<CharType, Traits>::epptr;
            // increment next pointer
            using std::basic_streambuf<CharType, Traits>::pbump;

          public:
            ODevFileStreamBuf() : m_pBuffer(0), m_file(0), m_pAdapter(0), m_fpos(0)
            {
            }

            ~ODevFileStreamBuf()
            {
                this->close();
            }

            filebuf_type* open(
                Spinnaker::GenApi::INodeMap* pInterface,
                const char* pFileName,
                std::ios_base::openmode mode)
            {

                // create GenICam Access
                m_pAdapter = new FileProtocolAdapter();

                // attach to node map
                if (!m_pAdapter || !m_pAdapter->attach(pInterface))
                {
                    delete m_pAdapter;
                    m_pAdapter = 0;
                    return 0;
                }

                // open file via Adapter
                if (!(m_pAdapter->openFile(pFileName, mode)))
                {
                    delete m_pAdapter;
                    m_pAdapter = 0;
                    return 0;
                }

                m_file = pFileName;
                // allocate buffer according to file info
                const int64_t bufSize = m_pAdapter->getBufSize(m_file, mode);
                m_pBuffer = new char_type[static_cast<size_t>(bufSize) / sizeof(char_type)];
                std::basic_streambuf<CharType, Traits>::setp(m_pBuffer, m_pBuffer + bufSize);

                return this;
            }

            bool is_open() const
            {
                return m_pAdapter != 0;
            }

            filebuf_type* close()
            {
                filebuf_type* ret = 0;
                bool syncFailed = false;
                if (this->is_open())
                {
                    if (sync())
                    {
                        syncFailed = true;
                    };
                    // close file
                    if (m_pAdapter->closeFile(m_file))
                    {
                        // no error
                        if (syncFailed)
                        {
                            ret = 0;
                        }
                        else
                        {
                            ret = this;
                        }
                    }
                    delete m_pAdapter;
                    m_pAdapter = 0;
                    // buffer
                    delete[] m_pBuffer;
                    m_pBuffer = 0;
                }
                return ret;
            }

          protected:
            std::streamsize xsputn(const char_type* s, std::streamsize n)
            {
                if (n < epptr() - pptr())
                {
                    memcpy(pptr(), s, n * sizeof(char_type));
                    pbump(static_cast<int>(n));
                    return n;
                }
                else
                {
                    for (std::streamsize i = 0; i < n; ++i)
                    {
                        if (traits_type::eq_int_type(
                                std::basic_streambuf<CharType, Traits>::sputc(s[i]), traits_type::eof()))
                            return i;
                    }
                    return n;
                }
            }
            int_type overflow(int_type c = traits_type::eof())
            {
                if (buffer_out() < 0)
                {
                    return traits_type::eof();
                }
                else
                {
                    if (!traits_type::eq_int_type(c, traits_type::eof()))
                        return std::basic_streambuf<CharType, Traits>::sputc(static_cast<char_type>(c));
                    else
                        return traits_type::not_eof(c);
                }
            }
            int sync()
            {
                return static_cast<int>(buffer_out());
            }

          private:
            char_type* m_pBuffer; // buffer[bufSize];
            const char* m_file;
            FileProtocolAdapter* m_pAdapter;
            int64_t m_fpos;

            int64_t buffer_out()
            {
                int64_t cnt = pptr() - pbase();

                int64_t retval;
                int64_t res = m_pAdapter->write(m_pBuffer, m_fpos, cnt, m_file);

                if (res != cnt)
                {
                    retval = -1;
                }
                else
                {
                    retval = 0;
                }
                m_fpos += res;

                pbump(-static_cast<int>(cnt));
                return retval;
            }

            // prohibit copying assignment
            ODevFileStreamBuf(const ODevFileStreamBuf&);
            ODevFileStreamBuf& operator=(const ODevFileStreamBuf&);
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup Filestream_h Filestream Class
         */
        /*@{*/

        template <typename CharType, typename Traits>
        class ODevFileStreamBase : public std::basic_ostream<CharType, Traits>
        {
          public:
            // Non-standard types:
            typedef ODevFileStreamBuf<CharType, Traits> filebuf_type;
            typedef std::basic_ios<CharType, Traits> ios_type;
            typedef std::basic_ostream<CharType, Traits> ostream_type;

          private:
            filebuf_type m_streambuf;

          public:
#if defined(_MSC_VER)
            ODevFileStreamBase() : ostream_type(std::_Noinit), m_streambuf()
            {
                this->init(&m_streambuf);
            }

            ODevFileStreamBase(
                Spinnaker::GenApi::INodeMap* pInterface,
                const char* pFileName,
                std::ios_base::openmode mode = std::ios_base::out | std::ios_base::trunc)
                : ostream_type(std::_Noinit), m_streambuf()
            {
                this->init(&m_streambuf);
                this->open(pInterface, pFileName, mode);
            };

#elif defined(__GNUC__)
            ODevFileStreamBase() : ostream_type(), m_streambuf()
            {
                this->init(&m_streambuf);
            }

            ODevFileStreamBase(
                INodeMap* pInterface,
                const char* pFileName,
                std::ios_base::openmode mode = std::ios_base::out | std::ios_base::trunc)
                : ostream_type(), m_streambuf()
            {
                this->init(&m_streambuf);
                this->open(pInterface, pFileName, mode);
            };

#else
#error Unknown C++ library
#endif

            filebuf_type* rdbuf() const
            {
                return const_cast<filebuf_type*>(&m_streambuf);
            }

            bool is_open() const
            {
                return m_streambuf.is_open();
            }

            /**
             * @brief Open file on device in write mode
             *
             * @param  pInterface  NodeMap of the device to which the FileProtocolAdapter is attached
             * @param  pFileName  Name of the file to open
             * @param  mode open mode
             */

            void open(
                INodeMap* pInterface,
                const char* pFileName,
                std::ios_base::openmode mode = std::ios_base::out | std::ios_base::trunc)
            {
                if (!m_streambuf.open(pInterface, pFileName, mode))
                {
                    this->setstate(std::ios_base::failbit);
                }
                else
                {
                    this->clear();
                }
            }

            /**
             *  @brief  Close the file on device
             */
            void close()
            {
                if (!m_streambuf.close())
                    this->setstate(std::ios_base::failbit);
            }
        };

        /*@}*/
        /*@}*/

        /**
         *  @addtogroup SpinnakerGenApiClasses Spinnaker GenApi Classes
         */
        /*@{*/

        /**
         *  @addtogroup Filestream_h Filestream Class
         */
        /*@{*/

        template <typename CharType, typename Traits>
        class IDevFileStreamBase : public std::basic_istream<CharType, Traits>
        {
          public:
            // Non-standard types:
            typedef IDevFileStreamBuf<CharType, Traits> filebuf_type;
            typedef std::basic_ios<CharType, Traits> ios_type;
            typedef std::basic_istream<CharType, Traits> istream_type;

          private:
            filebuf_type m_streambuf;

          public:
#if defined(_MSC_VER)
            IDevFileStreamBase() : istream_type(std::_Noinit), m_streambuf()
            {
                this->init(&m_streambuf);
            }

            IDevFileStreamBase(
                Spinnaker::GenApi::INodeMap* pInterface,
                const char* pFileName,
                std::ios_base::openmode mode = std::ios_base::in)
                : istream_type(std::_Noinit), m_streambuf()
            {
                this->init(&m_streambuf);
                this->open(pInterface, pFileName, mode);
            };

#elif defined(__GNUC__)
            IDevFileStreamBase() : istream_type(&m_streambuf), m_streambuf()
            {
                this->init(&m_streambuf);
            }

            IDevFileStreamBase(
                INodeMap* pInterface,
                const char* pFileName,
                std::ios_base::openmode mode = std::ios_base::in)
                : istream_type(&m_streambuf), m_streambuf()
            {
                this->init(&m_streambuf);
                this->open(pInterface, pFileName, mode);
            };

#else
#error Unknown C++ library
#endif

            filebuf_type* rdbuf() const
            {
                return const_cast<filebuf_type*>(&m_streambuf);
            }

            bool is_open() const
            {
                return m_streambuf.is_open();
            }

            /**
             * @brief Open file on device in write mode
             *
             * @param  pInterface  NodeMap of the device to which the FileProtocolAdapter is attached
             * @param  pFileName  Name of the file to open
             * @param  mode open mode
             */
            void open(
                Spinnaker::GenApi::INodeMap* pInterface,
                const char* pFileName,
                std::ios_base::openmode mode = std::ios_base::in)
            {
                if (!m_streambuf.open(pInterface, pFileName, mode))
                    this->setstate(std::ios_base::failbit);
                else
                    this->clear();
            }

            /**
             * @brief  Close the file on the device
             */
            void close()
            {
                if (!m_streambuf.close())
                    this->setstate(std::ios_base::failbit);
            }
        };

        /*@}*/
        /*@}*/

        typedef ODevFileStreamBase<char, std::char_traits<char>> ODevFileStream;
        typedef IDevFileStreamBase<char, std::char_traits<char>> IDevFileStream;
    } // namespace GenApi
} // namespace Spinnaker

#endif /*SPINNAKER_GENAPI_FILESTREAM_H_*/
