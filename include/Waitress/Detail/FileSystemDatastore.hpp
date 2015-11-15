/*********************************************************************************************************************/
/*                                                  /===-_---~~~~~~~~~------____                                     */
/*                                                 |===-~___                _,-'                                     */
/*                  -==\\                         `//~\\   ~~~~`---.___.-~~                                          */
/*              ______-==|                         | |  \\           _-~`                                            */
/*        __--~~~  ,-/-==\\                        | |   `\        ,'                                                */
/*     _-~       /'    |  \\                      / /      \      /                                                  */
/*   .'        /       |   \\                   /' /        \   /'                                                   */
/*  /  ____  /         |    \`\.__/-~~ ~ \ _ _/'  /          \/'                                                     */
/* /-'~    ~~~~~---__  |     ~-/~         ( )   /'        _--~`                                                      */
/*                   \_|      /        _)   ;  ),   __--~~                                                           */
/*                     '~~--_/      _-~/-  / \   '-~ \                                                               */
/*                    {\__--_/}    / \\_>- )<__\      \                                                              */
/*                    /'   (_/  _-~  | |__>--<__|      |                                                             */
/*                   |0  0 _/) )-~     | |__>--<__|     |                                                            */
/*                   / /~ ,_/       / /__>---<__/      |                                                             */
/*                  o o _//        /-~_>---<__-~      /                                                              */
/*                  (^(~          /~_>---<__-      _-~                                                               */
/*                 ,/|           /__>--<__/     _-~                                                                  */
/*              ,//('(          |__>--<__|     /                  .----_                                             */
/*             ( ( '))          |__>--<__|    |                 /' _---_~\                                           */
/*          `-)) )) (           |__>--<__|    |               /'  /     ~\`\                                         */
/*         ,/,'//( (             \__>--<__\    \            /'  //        ||                                         */
/*       ,( ( ((, ))              ~-__>--<_~-_  ~--____---~' _/'/        /'                                          */
/*     `~/  )` ) ,/|                 ~-_~>--<_/-__       __-~ _/                                                     */
/*   ._-~//( )/ )) `                    ~~-'_/_/ /~~~~~~~__--~                                                       */
/*    ;'( ')/ ,)(                              ~~~~~~~~~~                                                            */
/*   ' ') '( (/                                                                                                      */
/*     '   '  `                                                                                                      */
/*********************************************************************************************************************/
#ifndef _FILESYSTEM_DATASTORE_HPP_
#define _FILESYSTEM_DATASTORE_HPP_

#include <iterator>
#include <fstream>

namespace Waitress
{
    namespace Detail
    {
        template <typename Buffer>
        class FileSystemDatastore
        {
            public:
                using BufferType = Buffer;
                Buffer Get(const std::string& file);
        };

        template <typename Buffer>
        Buffer FileSystemDatastore<Buffer>::Get(const std::string& file)
        {
            // Open file
            std::ifstream ifs(file, std::ios::binary);
            if (!ifs.good())
                return Buffer();

            // Stop the istream_iterator from eating newlines
            ifs.unsetf(std::ios::skipws);

            // Calculate total filesize
            std::streampos sz;
            ifs.seekg(0, std::ios::end);
            sz = ifs.tellg();

            // Rewind file pointer
            ifs.seekg(0, std::ios::beg);

            // Create buffer with preallocated size
            Buffer buf(static_cast<std::size_t>(sz));

            // Read the data into the buffer
            buf.insert(std::begin(buf),
                       std::istream_iterator<typename Buffer::value_type>(ifs),
                       std::istream_iterator<typename Buffer::value_type>());

            return std::move(buf);
        }
    } // ! Detail
} // ! Waitress

#endif // ! _FILESYSTEM_DATASTORE_HPP_
