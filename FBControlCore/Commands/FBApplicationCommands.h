/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <Foundation/Foundation.h>

#import <FBControlCore/FBiOSTargetCommandForwarder.h>
#import <FBControlCore/FBFuture.h>

NS_ASSUME_NONNULL_BEGIN

@class FBApplicationLaunchConfiguration;
@class FBInstalledApplication;

/**
 Defines an interface for interacting with iOS Applications.
 */
@protocol FBApplicationCommands <NSObject, FBiOSTargetCommand>

/**
 Installs application at given path on the host.

 @param path the file path of the Application Bundle on the host.
 @return A future that resolves when successful.
 */
- (FBFuture<NSNull *> *)installApplicationWithPath:(NSString *)path;

/**
 Uninstalls application with given bundle id.

 @param bundleID the bundle id of the application to uninstall.
 @return A future that resolves when successful.
 */
- (FBFuture<NSNull *> *)uninstallApplicationWithBundleID:(NSString *)bundleID;

/**
 Queries to see if an Application is installed on iOS.

 @param bundleID The Bundle ID of the application.
 @param error an error out for any error that occurs.
 @return YES if the command succeeds, NO otherwise,
 */
- (BOOL)isApplicationInstalledWithBundleID:(NSString *)bundleID error:(NSError **)error;

/**
 Launches an Application with the provided Application Launch Configuration.

 @param configuration the Application Launch Configuration to use.
 @param error an error out for any error that occurs.
 @return YES if the operation succeeds, otherwise NO.
 */
- (BOOL)launchApplication:(FBApplicationLaunchConfiguration *)configuration error:(NSError **)error;

/**
 Kills application with given bundleID

 @param bundleID bundle ID of installed application
 @param error an error out for any error that occurs.
 @return YES if the operation succeeds, otherwise NO.
 */
- (BOOL)killApplicationWithBundleID:(NSString *)bundleID error:(NSError **)error;

/**
 Fetches a list of the Installed Applications.
 The returned FBApplicationBundle object is fully JSON Serializable.

 @return A future wrapping a List of Installed Applications.
 */
- (FBFuture<NSArray<FBInstalledApplication *> *> *)installedApplications;

@end

NS_ASSUME_NONNULL_END
