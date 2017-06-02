//
//  CDHarmonicFunction.m
//  ChartDrawer
//
//  Created by Teploukhova, Alisa on 01/06/17.
//  Copyright © 2017 Teploukhova, Alisa. All rights reserved.
//

#import "CDHarmonicFunction.h"

NSString *const CDHarmonicFunctionAmplitudeChanged = @"CDHarmonicFunctionAmplitudeChanged";
NSString *const CDHarmonicFunctionFrequencyChanged = @"CDHarmonicFunctionFrequencyChanged";
NSString *const CDHarmonicFunctionPhaseChanged = @"CDHarmonicFunctionPhaseChanged";

@implementation CDHarmonicFunction

- (instancetype)init {
    self = [super init];
    if (self) {
        _functionType = CDFunctionTypeSin;
        _amplitude = 1.0;
        _frequency = 1.0;
        _phase = 0.0;
    }
    return self;
}

- (instancetype)initWithFunctionType:(CDFunctionType)functionType amplitude:(double)amplitude frequency:(double)frequency phase:(double)phase {
    self = [super init];
    if (self) {
        _functionType = functionType;
        _amplitude = amplitude;
        _frequency = frequency;
        _phase = phase;
    }
    return self;
}

- (double)valueWithX:(double)x {
    switch (self.functionType) {
        case CDFunctionTypeSin:
            return self.amplitude * sin(self.frequency * x + self.phase);
        case CDFuncitonTypeCos:
            return self.amplitude * cos(self.frequency * x + self.phase);
        default:
            return 0.0;
    }
}

#pragma mark - Setters

- (void)setAmplitude:(double)amplitude {
    _amplitude = amplitude;
    [[NSNotificationCenter defaultCenter] postNotificationName:CDHarmonicFunctionAmplitudeChanged object:nil];
}

- (void)setFrequency:(double)frequency {
    _frequency = frequency;
    [[NSNotificationCenter defaultCenter] postNotificationName:CDHarmonicFunctionFrequencyChanged object:nil];
}

- (void)setPhase:(double)phase {
    _phase = phase;
    [[NSNotificationCenter defaultCenter] postNotificationName:CDHarmonicFunctionPhaseChanged object:nil];
}

#pragma mark - Presentation

- (NSString *)description {
    return [NSString stringWithFormat:@"%g*%@(%g*x + %g)", self.amplitude, [CDHarmonicFunction titleForFunctionType:self.functionType], self.frequency, self.phase];
}

+ (NSString *)titleForFunctionType:(CDFunctionType)functionType {
    switch (functionType) {
        case CDFunctionTypeSin:
            return @"sin";
        case CDFuncitonTypeCos:
            return @"cos";
        default:
            return nil;
    }
}

@end
