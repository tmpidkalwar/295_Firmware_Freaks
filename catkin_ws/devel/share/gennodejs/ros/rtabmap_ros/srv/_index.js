
"use strict";

let GetPlan = require('./GetPlan.js')
let CleanupLocalGrids = require('./CleanupLocalGrids.js')
let GlobalBundleAdjustment = require('./GlobalBundleAdjustment.js')
let ResetPose = require('./ResetPose.js')
let GetMap = require('./GetMap.js')
let GetNodesInRadius = require('./GetNodesInRadius.js')
let GetMap2 = require('./GetMap2.js')
let DetectMoreLoopClosures = require('./DetectMoreLoopClosures.js')
let AddLink = require('./AddLink.js')
let SetLabel = require('./SetLabel.js')
let LoadDatabase = require('./LoadDatabase.js')
let ListLabels = require('./ListLabels.js')
let GetNodeData = require('./GetNodeData.js')
let PublishMap = require('./PublishMap.js')
let SetGoal = require('./SetGoal.js')

module.exports = {
  GetPlan: GetPlan,
  CleanupLocalGrids: CleanupLocalGrids,
  GlobalBundleAdjustment: GlobalBundleAdjustment,
  ResetPose: ResetPose,
  GetMap: GetMap,
  GetNodesInRadius: GetNodesInRadius,
  GetMap2: GetMap2,
  DetectMoreLoopClosures: DetectMoreLoopClosures,
  AddLink: AddLink,
  SetLabel: SetLabel,
  LoadDatabase: LoadDatabase,
  ListLabels: ListLabels,
  GetNodeData: GetNodeData,
  PublishMap: PublishMap,
  SetGoal: SetGoal,
};
