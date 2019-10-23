// args.hpp  -----------------------------------------------------------------//
// -----------------------------------------------------------------------------

// Copyright 2011-2014 Renato Tegon Forti

// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt

// -----------------------------------------------------------------------------

// Revision History
// 14-10-2013 dd-mm-yyyy - Initial Release

// -----------------------------------------------------------------------------

#ifndef BOOST_APPLICATION_ARGS_ASPECT_HPP
#define BOOST_APPLICATION_ARGS_ASPECT_HPP

#include <boost/application/base_type.hpp>
#include <boost/application/config.hpp>
#include <exception>


#if _WIN32
#include <shellapi.h>
#include <Windows.h>
#endif

namespace boost
{
namespace application
{
/*!
 * \brief This aspect class handle application args in more friedly way.
 *
 * An aspect that will hold args, and provide a easy way to access they
 * or user can extrat args from it to use with Program_options,
 * getopts or argp and so on.
 *
 */
template<typename CharType>
class args_
{
public:
    // string types to be used internaly to handle unicode on windows
    typedef CharType char_type;
    typedef std::basic_string<char_type> string_type;

    /*!
     * Constructs an args_.
     *
     * \param argc An argc from main.
     * \param argc An argv from main.
     */
    args_(int argc, char_type* argv[])
    {
        for (int i = 0; i < argc; i++)
            arguments_.push_back(argv[i]);
    }

#if _WIN32
    /*!
     * Constructs an args_.
     *
     * \param argc An argc from main.
     * \param argc An argv from main.
     */
    args_(LPTSTR lpCmdLine)
    {
        LPWSTR* szArglist;
        int nArgs;
        int i;

        szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
        if (NULL == szArglist)
        {
            throw new std::exception("CommandLineToArgvW failed\n");
        }
        else
        {
            for (i = 0; i < nArgs; i++)
            {
                arguments_.push_back(szArglist[i]);
            }
        }

        // Free memory allocated for CommandLineToArgvW arguments.

        LocalFree(szArglist);
    }
#endif

    /*!
     * Get a argc as provided by main.
     *
     * \return an argc variable.
     *
     */
    int argc() const { return (int)arguments_.size(); }

    /*!
     * Get a argv as provided by main.
     *
     * \return an argv variable.
     *
     */
    char_type** argv() { return &arguments_[0]; }

    /*!
     * Get a vector of args.
     *
     * \return an vector of args.
     *
     */
    std::vector<string_type> arg_vector()
    {
        std::vector<string_type> args;
        for (int i = 0; i < argc(); ++i)
            args.push_back(argv()[i]);

        return args;
    }

private:
    std::vector<char_type*> arguments_;
};

/////////////////////////////////////////////////////////////////////////////
// args
//

// args versions for Multi-Byte string and Unicode string
typedef args_<character_types::char_type> args;
// wchar_t / char

} // namespace application
} // namespace boost

#endif // BOOST_APPLICATION_ARGS_ASPECT_HPP
