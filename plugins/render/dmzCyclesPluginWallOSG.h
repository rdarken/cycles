#ifndef DMZ_CYCLES_PLUGIN_WALL_OSG_DOT_H
#define DMZ_CYCLES_PLUGIN_WALL_OSG_DOT_H

#include <dmzObjectObserverUtil.h>
#include <dmzRuntimeLog.h>
#include <dmzRuntimePlugin.h>
#include <dmzTypesHashTableHandleTemplate.h>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/ref_ptr>

namespace dmz {

   class RenderModuleCoreOSG;

   class CyclesPluginWallOSG :
         public Plugin,
         public ObjectObserverUtil {

      public:
         CyclesPluginWallOSG (const PluginInfo &Info, Config &local);
         ~CyclesPluginWallOSG ();

         // Plugin Interface
         virtual void update_plugin_state (
            const PluginStateEnum State,
            const UInt32 Level);

         virtual void discover_plugin (
            const PluginDiscoverEnum Mode,
            const Plugin *PluginPtr);

         // Object Observer Interface
         virtual void create_object (
            const UUID &Identity,
            const Handle ObjectHandle,
            const ObjectType &Type,
            const ObjectLocalityEnum Locality);

         virtual void destroy_object (const UUID &Identity, const Handle ObjectHandle);

         virtual void update_object_state (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Mask &Value,
            const Mask *PreviousValue);

         virtual void update_object_position (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Vector &Value,
            const Vector *PreviousValue);

         virtual void update_object_velocity (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Vector &Value,
            const Vector *PreviousValue);

      protected:
         struct WallStruct {

            const Boolean ColorDefined;
            const osg::Vec4 Color;
            const Float32 Height;

            WallStruct (
                  const Boolean IsColorDefined,
                  const osg::Vec4 TheColor,
                  const Float32 TheHeight) :
                  ColorDefined (IsColorDefined),
                  Color (TheColor),
                  Height (TheHeight) {;}
         };

         struct ObjectStruct {

            const WallStruct &WallInfo;
            osg::ref_ptr<osg::MatrixTransform> d;
            osg::ref_ptr<osg::Geometry> wall;

            ObjectStruct (const WallStruct &TheWallInfo) : WallInfo (TheWallInfo) {;}
         };

         void _create_wall (const Handle ObjectHandle, const WallStruct &Wall);
         void _init (Config &local);

         Log _log;
         HashTableHandleTemplate<ObjectStruct> _objectTable;
         HashTableHandleTemplate<WallStruct> _wallTable;
         RenderModuleCoreOSG *_core;

      private:
         CyclesPluginWallOSG ();
         CyclesPluginWallOSG (const CyclesPluginWallOSG &);
         CyclesPluginWallOSG &operator= (const CyclesPluginWallOSG &);

   };
};

#endif // DMZ_CYCLES_PLUGIN_WALL_OSG_DOT_H