
(cl:in-package :asdf)

(defsystem "rtabmap_ros-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :rtabmap_ros-msg
)
  :components ((:file "_package")
    (:file "AddLink" :depends-on ("_package_AddLink"))
    (:file "_package_AddLink" :depends-on ("_package"))
    (:file "CleanupLocalGrids" :depends-on ("_package_CleanupLocalGrids"))
    (:file "_package_CleanupLocalGrids" :depends-on ("_package"))
    (:file "DetectMoreLoopClosures" :depends-on ("_package_DetectMoreLoopClosures"))
    (:file "_package_DetectMoreLoopClosures" :depends-on ("_package"))
    (:file "GetMap" :depends-on ("_package_GetMap"))
    (:file "_package_GetMap" :depends-on ("_package"))
    (:file "GetMap2" :depends-on ("_package_GetMap2"))
    (:file "_package_GetMap2" :depends-on ("_package"))
    (:file "GetNodeData" :depends-on ("_package_GetNodeData"))
    (:file "_package_GetNodeData" :depends-on ("_package"))
    (:file "GetNodesInRadius" :depends-on ("_package_GetNodesInRadius"))
    (:file "_package_GetNodesInRadius" :depends-on ("_package"))
    (:file "GetPlan" :depends-on ("_package_GetPlan"))
    (:file "_package_GetPlan" :depends-on ("_package"))
    (:file "GlobalBundleAdjustment" :depends-on ("_package_GlobalBundleAdjustment"))
    (:file "_package_GlobalBundleAdjustment" :depends-on ("_package"))
    (:file "ListLabels" :depends-on ("_package_ListLabels"))
    (:file "_package_ListLabels" :depends-on ("_package"))
    (:file "LoadDatabase" :depends-on ("_package_LoadDatabase"))
    (:file "_package_LoadDatabase" :depends-on ("_package"))
    (:file "PublishMap" :depends-on ("_package_PublishMap"))
    (:file "_package_PublishMap" :depends-on ("_package"))
    (:file "ResetPose" :depends-on ("_package_ResetPose"))
    (:file "_package_ResetPose" :depends-on ("_package"))
    (:file "SetGoal" :depends-on ("_package_SetGoal"))
    (:file "_package_SetGoal" :depends-on ("_package"))
    (:file "SetLabel" :depends-on ("_package_SetLabel"))
    (:file "_package_SetLabel" :depends-on ("_package"))
  ))