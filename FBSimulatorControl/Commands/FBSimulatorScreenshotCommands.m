/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import "FBSimulatorScreenshotCommands.h"

#import "FBFramebuffer.h"
#import "FBSimulator.h"
#import "FBSimulatorError.h"
#import "FBSimulatorImage.h"

@interface FBSimulatorScreenshotCommands ()

@property (nonatomic, strong, readonly) FBSimulator *simulator;

@end

@implementation FBSimulatorScreenshotCommands

#pragma mark Initializers

+ (instancetype)commandsWithTarget:(id<FBiOSTarget>)target
{
  NSParameterAssert([target isKindOfClass:FBSimulator.class]);
  return [[self alloc] initWithSimulator:(FBSimulator *) target];
}

- (instancetype)initWithSimulator:(FBSimulator *)simulator
{
  self = [super init];
  if (!self) {
    return nil;
  }

  _simulator = simulator;

  return self;
}

#pragma mark FBScreenshotCommands

- (FBFuture<NSData *> *)takeScreenshot:(FBScreenshotFormat)format
{
  NSError *error = nil;
  FBFramebuffer *framebuffer = [self.simulator framebufferWithError:&error];
  if (!framebuffer) {
    return [FBFuture futureWithError:error];
  }
  FBSimulatorImage *image = framebuffer.image;
  NSData *data = nil;
  if ([format isEqualToString:FBScreenshotFormatJPEG]) {
    data = [image jpegImageDataWithError:&error];
  } else if ([format isEqualToString:FBScreenshotFormatPNG]) {
    data = [image pngImageDataWithError:&error];
  } else {
    return [[FBSimulatorError
      describeFormat:@"%@ is not a recognized screenshot format", format]
      failFuture];
  }
  return data ? [FBFuture futureWithResult:data] : [FBFuture futureWithError:error];
}

@end
