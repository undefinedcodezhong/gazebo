/*
 * Copyright (C) 2012-2013 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef _ENTITY_MANIPULATOR_HH_
#define _ENTITY_MANIPULATOR_HH_

#include <string>

#include "gazebo/common/MouseEvent.hh"
#include "gazebo/common/KeyEvent.hh"

#include "gazebo/transport/TransportTypes.hh"

#include "gazebo/rendering/RenderTypes.hh"

#include "gazebo/common/SingletonT.hh"

namespace gazebo
{
  namespace gui
  {
    /// \class EntityManipulator EntityManipulator.hh gui/Gui.hh
    /// \brief Manipulator tool for translating/rotating/scaling models and
    /// links
    class EntityManipulator : public SingletonT<EntityManipulator>
    {
      /// \brief Constructor
      private: EntityManipulator();

      /// \brief Destructor
      private: virtual ~EntityManipulator();

      /// \brief Initialize the model manipulator.
      public: void Init();

      /// \brief Set the manipulation mode.
      /// \param[in] _mode Manipulation mode: translate, rotate, or scale.
      public: void SetManipulationMode(const std::string &_mode);

      /// \brief Set the visual to be manipulated by the model manipulator.
      public: void SetAttachedVisual(rendering::VisualPtr _vis);

      /// \brief Process an object translate mouse press event.
      /// \param[in] _event Mouse event.
      public: void OnMousePressEvent(const common::MouseEvent &_event);

      /// \brief Process an object translate mouse move event.
      /// \param[in] _event Mouse event.
      public: void OnMouseMoveEvent(const common::MouseEvent &_event);

      /// \brief Process an object translate mouse release event.
      /// \param[in] _event Mouse event.
      public: void OnMouseReleaseEvent(const common::MouseEvent &_event);

      /// \brief Process a key press event.
      /// \param[in] _event Key event.
      public: void OnKeyPressEvent(const common::KeyEvent &_event);

      /// \brief Process a key release event.
      /// \param[in] _event Key event.
      public: void OnKeyReleaseEvent(const common::KeyEvent &_event);

      /// \brief Rotate entity.
      /// \param[in] _vis Visual representing the entity.
      /// \param[in] _axis Axis of rotation.
      /// \param[in] _local True to apply rotation in local frame.
      public: void RotateEntity(rendering::VisualPtr &_vis,
          const math::Vector3 &_axis,
          bool _local = false);

      /// \brief Translate entity.
      /// \param[in] _vis Visual representing the entity.
      /// \param[in] _axis Axis of translation.
      /// \param[in] _local True to apply translation in local frame.
      public: void TranslateEntity(rendering::VisualPtr &_vis,
          const math::Vector3 &_axis,
          bool _local = false);

      /// \brief Scale entity.
      /// \param[in] _vis Visual representing the entity.
      /// \param[in] _axis Scaling axis.
      /// \param[in] _local True to apply scaling in local frame.
      public: void ScaleEntity(rendering::VisualPtr &_vis,
          const math::Vector3 &_axis,
          bool _local = false);

      /// \brief Snap a point at intervals of a fixed distance. Currently used
      /// to give a snapping behavior when moving models with a mouse.
      /// \param[in] _point Input point.
      /// \param[in] _interval Fixed distance interval at which the point
      /// is snapped.
      /// \param[in] _sensitivity Sensitivity of point snapping, in terms of a
      /// percentage of the interval.
      /// \return Snapped 3D point.
      public: static math::Vector3 SnapPoint(const math::Vector3 &_point,
          double _interval = 1.0, double _sensitivity = 0.4);

      /// \brief Helper function to get the 3D position of mouse on ground
      /// plane.
      /// param[in] _camera Pointer to user camera.
      /// param[in] _event Mouse event.
      /// return Point of mouse-plane intersection in world coordinates.
      public: static math::Vector3 GetMousePositionOnPlane(
          rendering::CameraPtr _camera,
          const common::MouseEvent &_event);

      /// \brief Helper function to get the distance moved by the mouse.
      /// \param[in] _camera Pointer to user camera.
      /// \param[in] _pose Pose of origin.
      /// \param[in] _axis Movement axis.
      /// \param[in] _local True to get distance in local frame.
      /// \return Mouse distance moved.
      public: static math::Vector3 GetMouseMoveDistance(
          rendering::CameraPtr _camera,
          const math::Vector2i &_start, const math::Vector2i &_end,
          const math::Pose &_pose, const math::Vector3 &_axis,
          bool _local);

      /// \brief Helper function to get the distance moved by the mouse.
      /// \param[in] _pose Pose of origin.
      /// \param[in] _axis Movement axis.
      /// \param[in] _local True to get distance in local frame.
      /// \return Mouse distance moved.
      private: math::Vector3 GetMouseMoveDistance(const math::Pose &_pose,
          const math::Vector3 &_axis, bool _local) const;

      /// \brief Set the visual being moved by the mouse.
      /// \param[in] _vis Pointer to visual moved by mouse.
      private: void SetMouseMoveVisual(rendering::VisualPtr _vis);

      /// \brief Publish visual's pose to the server
      /// \param[in] _vis Pointer to the visual whose pose is to be published.
      private: void PublishVisualPose(rendering::VisualPtr _vis);

      /// \brief Publish visual's scale to the server
      /// \param[in] _vis Pointer to the visual whose scale is to be published.
      private: void PublishVisualScale(rendering::VisualPtr _vis);

      /// \brief Selection object which users can interact with to manipulate
      /// the model.
      private: rendering::SelectionObjPtr selectionObj;

      /// \brief The current manipulation mode.
      private: std::string manipMode;

      /// \brief Keep track of the mouse start pose before a move action.
      private: math::Pose mouseMoveVisStartPose;

      /// \brief Keep track of the mouse start screen position.
      private: math::Vector2i mouseStart;

      /// \brief The current selected visual.
      private: rendering::VisualPtr selectedVis;

      /// \brief The current visual attached to the mouse.
      private: rendering::VisualPtr mouseMoveVis;

      /// \brief Transportation node.
      private: transport::NodePtr node;

      /// \brief Model publisher that publishes model pose to the server.
      private: transport::PublisherPtr modelPub;

      /// \brief Light publisher that publishes light pose to the server.
      private: transport::PublisherPtr lightPub;

      /// \brief Pointer to the user camera.
      private: rendering::UserCameraPtr userCamera;

      /// \brief Pointer to the scene where models are in.
      private: rendering::ScenePtr scene;

      /// \brief Current mouse event.
      private: common::MouseEvent mouseEvent;

      /// \brief Current key event.
      private: common::KeyEvent keyEvent;

      /// \brief True if the model manipulator is initialized.
      private: bool initialized;

      /// \brief Scale of the visual attached to the mouse.
      private: math::Vector3 mouseVisualScale;

      /// \brief Bounding box of the visual attached to the mouse (for scaling).
      private: math::Box mouseVisualBbox;

      /// \brief True to manipulate model in global frame.
      private: bool globalManip;

      /// \brief True to manipulate model, false manipulates link
      private: bool controlLink;

      /// \brief This is a singleton class.
      private: friend class SingletonT<EntityManipulator>;
    };
  }
}
#endif
