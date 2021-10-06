
(cl:in-package :asdf)

(defsystem "navigation-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "set_initial_pose" :depends-on ("_package_set_initial_pose"))
    (:file "_package_set_initial_pose" :depends-on ("_package"))
  ))