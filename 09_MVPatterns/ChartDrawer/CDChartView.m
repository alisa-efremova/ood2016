//
//  CDChartView.m
//  ChartDrawer
//
//  Created by Teploukhova, Alisa on 05/06/17.
//  Copyright © 2017 Teploukhova, Alisa. All rights reserved.
//

#import "CDChartView.h"

@implementation CDChartView

#pragma mark - Initialization

- (nonnull instancetype)init {
    self = [super init];
    if (self) {
        _step = 0.0;
    }
    return self;
}

- (nullable id)initWithCoder:(nonnull NSCoder *)coder {
    self = [super initWithCoder:coder];
    if (self) {
        _step = 0.0;
    }
    return self;
}

- (nonnull instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        _step = 0.0;
    }
    return self;
}

#pragma mark - Setters

- (void)setStep:(double)step {
    _step = step;
    [self setNeedsDisplay];
}

- (void)setValues:(NSArray<NSNumber *> *)values {
    _values = [values copy];
    [self setNeedsDisplay];
}

#pragma mark - UIViewRendering

- (void)drawRect:(CGRect)rect {
    NSLog(@"DRAW");
    [self drawAxes];
    [self drawGraph];
}

#pragma mark - Drawing Helpers

- (void)drawAxes {
    double width = self.bounds.size.width;
    double height = self.bounds.size.height;
    
    [[UIColor lightGrayColor] setStroke];
    UIBezierPath *path = [UIBezierPath bezierPath];
    path.lineWidth = 1.0;
    [path moveToPoint:CGPointMake(0, 0)];
    [path addLineToPoint:CGPointMake(0, height)];
    [path moveToPoint:CGPointMake(0, height/2)];
    [path addLineToPoint:CGPointMake(width, height/2)];
    
    [path stroke];
}

- (void)drawGraph {
    if ([self.values count] == 0 || self.step == 0) {
        return;
    }
    
    // find max Y
    double maxY = 0;
    for (NSNumber *value in self.values) {
        double tmp = [value doubleValue] < 0 ? -[value doubleValue] : [value doubleValue];
        maxY = MAX(maxY, tmp);
    }
 
    double width = self.bounds.size.width;
    double height = self.bounds.size.height;
    NSUInteger size = [self.values count];
    
    
    [[UIColor blueColor] setStroke];
    UIBezierPath *path = [UIBezierPath bezierPath];
    path.lineWidth = 1.0;
    
    [path moveToPoint:CGPointMake(0, height/2 - [self.values[0] doubleValue] * height/2/maxY)];
    for (int i = 1; i < size; i++) {
        double realX = i * self.step;
        double realY = [self.values[i] doubleValue];
        double scaledX = realX * width/size/self.step;
        double scaledY = height/2 - realY * height/2/maxY;
       [path addLineToPoint:CGPointMake(scaledX, scaledY)];
    }
    
    [path stroke];
}

@end
