//
//  CDHarmonicFunction.h
//  ChartDrawer
//
//  Created by Teploukhova, Alisa on 01/06/17.
//  Copyright © 2017 Teploukhova, Alisa. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, CDFunctionType) {
    CDFunctionTypeSin,
    CDFuncitonTypeCos
};

@interface CDHarmonicFunction : NSObject
@property (nonatomic) double amplitude;
@property (nonatomic) CDFunctionType type;
@property (nonatomic) double frequency;
@property (nonatomic) double phase;

- (instancetype)initWithFunctionType:(CDFunctionType)functionType amplitude:(double)amplitude frequency:(double)frequency phase:(double)phase;

- (double)valueWithX:(double)x;

@end

