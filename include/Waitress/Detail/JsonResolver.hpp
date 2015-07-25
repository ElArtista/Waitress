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
#ifndef _JSON_RESOLVER_HPP_
#define _JSON_RESOLVER_HPP_

#include <string>
#include <map>
#include <rapidjson/document.h>

namespace Waitress
{
    namespace Detail
    {
        class JsonResolver
        {
            public:
                std::string Resolve(const std::string& id)
                {
                    const auto it = idMap.find(id);
                    if (it != idMap.end())
                        return it->second;
                    else
                        return "";
                }

                bool LoadIdMap(const std::string& jsonContents)
                {
                    using namespace rapidjson;
                    idMap.clear();

                    Document d;
                    d.Parse(jsonContents.c_str());
                    if(d.HasParseError())
                        return false;
                    
                    if (!d.IsArray())
                        return false;

                    for (SizeType i = 0; i < d.Size(); i++)
                    {
                        const auto& e = d[i];
                        if (!e.IsObject())
                            return false;

                        if (!e.HasMember("id") || !e.HasMember("path"))       
                            return false;

                        const auto& id = e["id"];
                        const auto& path = e["path"];
                        if (!id.IsString() || !path.IsString())
                            return false;

                        idMap.insert(std::make_pair<std::string, std::string>(id.GetString(), path.GetString()));
                    }
                    return true;
                }
            private:
                std::map<std::string, std::string> idMap;
        };
    } // ! Detail
} // ! Waitress

#endif // ! _JSON_RESOLVER_HPP_
