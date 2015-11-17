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
#ifndef _RESMAN_HPP_
#define _RESMAN_HPP_

#include <string>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Buffer.hpp"
#include "Datastore.hpp"
#include "Resolver.hpp"

namespace Waitress
{
    template <template<class> class Datastore,
              typename Resolver = DefaultResolver,
              typename Buffer = DefaultBuffer>
    class ResMan
    {
        public:
            // Forward the template params
            using DatastoreType = Datastore<Buffer>;
            using ResolverType = Resolver;
            using BufferType = Buffer;

            // Loads and returns the resource data buffer with the specified uri
            const BufferType* Load(const std::string& uri);

            // Unloads the resource data with the specified uri
            void Unload(const std::string& uri);

            // Retrieves the data buffer for the specified uri
            const BufferType* Get(const std::string& uri);

            // Retrieves the internal resolver object
            ResolverType& GetResolver();

            // Retrieves the internal datastore object
            Datastore<Buffer>& GetDatastore();

        private:
            // Used to translate given Uri's to a filepath for accessing resources in the datastore
            Resolver mResolver;

            // Used to access the data
            Datastore<Buffer> mDatastore;

            // Holds the loaded asset data
            std::unordered_map<std::string, Buffer> mDataMap;
    };

    template <template<class> class Datastore, typename Resolver, typename Buffer>
    const Buffer* ResMan<Datastore, Resolver, Buffer>::Load(const std::string& uri)
    {
        // The translated uri
        std::string filepath = mResolver.Resolve(uri);

        // The buffer that will hold the loaded data
        std::unique_ptr<Buffer> buf;

        // Get the data from the Datastore
        buf = mDatastore.Get(filepath);

        // Check if load was successful
        if (!buf)
            return nullptr;

        // Move the buffer onto the buffer holder
        std::pair<typename decltype(mDataMap)::iterator, bool> p = mDataMap.emplace(std::make_pair(uri, std::move(*buf)));

        // Return ptr to the stored buffer
        return &((*(p.first)).second);
    }

    template <template<class> class Datastore, typename Resolver, typename Buffer>
    void ResMan<Datastore, Resolver, Buffer>::Unload(const std::string& uri)
    {
        // Iterator to the element to removed
        auto it = mDataMap.find(uri);
        // Remove the element
        mDataMap.erase(it);
    }

    template <template<class> class Datastore, typename Resolver, typename Buffer>
    const Buffer* ResMan<Datastore, Resolver, Buffer>::Get(const std::string& uri)
    {
        auto it = mDataMap.find(uri);
        if (it == std::end(mDataMap))
            return nullptr;
        else
            return &(*it).second;
    }

    template <template<class> class Datastore, typename Resolver, typename Buffer>
    Resolver& ResMan<Datastore, Resolver, Buffer>::GetResolver()
    {
        return mResolver;
    }

    template <template<class> class Datastore, typename Resolver, typename Buffer>
    Datastore<Buffer>& ResMan<Datastore, Resolver, Buffer>::GetDatastore()
    {
        return mDatastore;
    }
}

#endif // ! _RESMAN_HPP_
