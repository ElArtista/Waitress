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

/**
 * Datastore
 *   Encapsulates the access strategy to a datasource location
 * 
 * Requirements:
 *   Given:
 *     * DS, a Datastore type
 *     * ds, an object of type DS
 *   Then:
 *     Expression        | Requirements                      | Return type
 *     ------------------------------------------------------------------------------------------------------------
 *     DS::IteratorType  | Satisfies InputIterator concept   | The iterator type that is used to access the resource
 *     ds.Get(uri)       | uri is convertible to std::string | An instance of type DS::IteratorType [0]
 *     
 *   Notes:
 *     [0]: The iterator points to the beggining of the stream
 */

/**
 * Resolver
 *   Converts the given resource identifier to an actual
 *   resource uri used by the Datastore
 * 
 * Requirements:
 *   Given:
 *     * R, a Resolver type
 *     * r, an object of type R
 *   Then:
 *     Expression    | Requirements                     | Return type
 *     ------------------------------------------------------------------
 *     r.Resolve(id) | id is convertible to std::string | std::string [0]
 *     
 *   Notes:
 *     [0]: The resolved uri that is unique to each resource identifier
 */

#endif // ! _RESMAN_HPP_
