//
//  CDHarmonicFunction.m
//  ChartDrawer
//
//  Created by Teploukhova, Alisa on 01/06/17.
//  Copyright © 2017 Teploukhova, Alisa. All rights reserved.
//

#import "CDHarmonicFunction.h"

@implementation CDHarmonicFunction

- (instancetype)init {
    self = [super init];
    if (self) {
        _type = CDFunctionTypeSin;
        _amplitude = 1.0;
        _frequency = 1.0;
        _phase = 0.0;
    }
    return self;
}

- (instancetype)initWithFunctionType:(CDFunctionType)functionType amplitude:(double)amplitude frequency:(double)frequency phase:(double)phase {
    self = [super init];
    if (self) {
        _type = functionType;
        _amplitude = amplitude;
        _frequency = frequency;
        _phase = phase;
    }
    return self;
}

- (double)valueWithX:(double)x {
    switch (self.type) {
        case CDFunctionTypeSin:
            return self.amplitude * sin(self.frequency * x + self.phase);
        case CDFunctionTypeCos:
            return self.amplitude * cos(self.frequency * x + self.phase);
        default:
            return 0.0;
    }
}

#pragma mark - Presentation

- (NSString *)description {
    return [NSString stringWithFormat:@"%g*%@(%g*x + %g)", self.amplitude, [CDHarmonicFunction titleForFunctionType:self.type], self.frequency, self.phase];
}

+ (NSString *)titleForFunctionType:(CDFunctionType)functionType {
    switch (functionType) {
        case CDFunctionTypeSin:
            return @"sin";
        case CDFunctionTypeCos:
            return @"cos";
        default:
            return nil;
    }
}

@end
