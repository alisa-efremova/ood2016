//
//  CDChartView.m
//  ChartDrawer
//
//  Created by Teploukhova, Alisa on 05/06/17.
//  Copyright © 2017 Teploukhova, Alisa. All rights reserved.
//

#import "CDChartView.h"

@interface CDChartView ()
@property (nonatomic, copy) NSDictionary * legendFontAttributes;
@end

@implementation CDChartView

#pragma mark - Initialization

- (instancetype)init {
    self = [super init];
    if (self) {
        _step = 0.0;
    }
    return self;
}

- (id)initWithCoder:(NSCoder *)coder {
    self = [super initWithCoder:coder];
    if (self) {
        _step = 0.0;
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame {
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
    [self drawAxes];
    [self drawGraph];
}

#pragma mark - Drawing Helpers

static double kLeftPadding = 30.0;
static double kTopPadding = 10.0;
static double kBottomPadding = 10.0;

static double kHAxisWidth = 0.5;
static double kVAxisWidth = 0.5;

static double kMinHLegendSpacing = 20.0;
static double kMinVLegendSpacing = 20.0;

- (void)drawAxes {
    double width = [self chartWidth];
    double height = [self chartHeight];
    
    [[UIColor lightGrayColor] setStroke];
    UIBezierPath *pathAxisY = [UIBezierPath bezierPath];
    pathAxisY.lineWidth = kVAxisWidth;
    [pathAxisY moveToPoint:CGPointMake(0, 0)];
    [pathAxisY addLineToPoint:CGPointMake(0, height)];
    [pathAxisY applyTransform:CGAffineTransformTranslate(CGAffineTransformIdentity, kLeftPadding, kTopPadding)];
    [pathAxisY stroke];
    
    UIBezierPath *pathAxisX = [UIBezierPath bezierPath];
    pathAxisX.lineWidth = kHAxisWidth;
    if ([self.values count] == 0) {
        // draw only main OX
        [pathAxisX moveToPoint:CGPointMake(0, height/2)];
        [pathAxisX addLineToPoint:CGPointMake(width, height/2)];
    } else {
        // draw main and secondary OXs
        double YLegendStep = [self YLegendStep];
        NSInteger maxY = [self maxIntegerY];
        double stepY = height/maxY/2 * YLegendStep;
        for (int i = 0; i <= maxY * 2 / YLegendStep; i++) {
            [pathAxisX moveToPoint:CGPointMake(0, i * stepY)];
            [pathAxisX addLineToPoint:CGPointMake(width, i * stepY)];
        }
        [pathAxisX applyTransform:CGAffineTransformTranslate(CGAffineTransformIdentity, kLeftPadding, kTopPadding)];
        [pathAxisX stroke];
        
        // y legend
        NSString *maxString = [NSString stringWithFormat:@"-%ld", maxY];
        CGSize stringSize = [maxString sizeWithAttributes:self.legendFontAttributes];
        double currentY = maxY;
        double x = kLeftPadding - stringSize.width - 10;
        for (int i = 0; i <= maxY * 2 / YLegendStep; i++) {
            double y = i * stepY - stringSize.height/2 + kTopPadding;
            NSString *string = [NSString stringWithFormat:@"%.0f", currentY];
            currentY -= YLegendStep;
            [string drawInRect:CGRectMake(x, y, stringSize.width + 5, stringSize.height) withAttributes:self.legendFontAttributes];
        }
        
        // x legend
        double XLegendStep = [self XLegendStep];
        NSInteger maxX = [self maxIntegerX];
        double stepX = width/maxX * XLegendStep;
        double y = stepY * maxY/2 + kTopPadding + 5;
        
        NSString *maxXString = [NSString stringWithFormat:@"%ld", maxX];
        CGSize stringXSize = [maxXString sizeWithAttributes:self.legendFontAttributes];
        double currentX = 0;
        for (int i = 0; i <= maxX / XLegendStep; i++) {
            double x =  i * stepX - stringSize.width/2 + kLeftPadding;
            NSString *string = [NSString stringWithFormat:@"%.0f", currentX];
            currentX += XLegendStep;
            [string drawInRect:CGRectMake(x, y, stringXSize.width + 5, stringXSize.height) withAttributes:self.legendFontAttributes];
        }
    }
}

- (void)drawGraph {
    if ([self.values count] == 0 || self.step == 0) {
        return;
    }
    
    double width = [self chartWidth];
    double height = [self chartHeight];
    NSUInteger size = [self.values count];
    NSInteger maxY = [self maxIntegerY];
    
    [[UIColor blueColor] setStroke];
    UIBezierPath *path = [UIBezierPath bezierPath];
    path.lineWidth = 1.0;
    
    [path moveToPoint:CGPointMake(0, maxY - [self.values[0] doubleValue])];
    for (int i = 1; i < size; i++) {
        double x = i * self.step;
        double y = maxY - [self.values[i] doubleValue];
        [path addLineToPoint:CGPointMake(x, y)];
    }
    [path applyTransform:CGAffineTransformScale(CGAffineTransformIdentity, width/size/self.step, height/2/maxY)];
    [path applyTransform:CGAffineTransformTranslate(CGAffineTransformIdentity, kLeftPadding, kTopPadding)];
    [path stroke];
}

#pragma mark - Calculating Helpers

- (double)maxY {
    double maxY = 0;
    for (NSNumber *value in self.values) {
        double tmp = [value doubleValue] < 0 ? -[value doubleValue] : [value doubleValue];
        maxY = MAX(maxY, tmp);
    }
    return maxY;
}

- (double)maxX {
    return ([self.values count] - 1) * self.step;
}

- (NSInteger)maxIntegerY {
    double YLegendStep = [self YLegendStep];
    return (NSInteger)ceil([self maxY]/YLegendStep) * YLegendStep;
}

- (NSInteger)maxIntegerX {
    double XLegendStep = [self XLegendStep];
    return (NSInteger)ceil([self maxX]/XLegendStep) * XLegendStep;
}

- (double)chartWidth {
    return self.bounds.size.width - kLeftPadding;
}

- (double)chartHeight {
    return self.bounds.size.height - kTopPadding - kBottomPadding;
}

- (double)YLegendStep {
    double legendHeight = [@"1" sizeWithAttributes:self.legendFontAttributes].height + kMinVLegendSpacing;
    double maxPositiveLegendCount = ([self chartHeight]/legendHeight + 1)/2;
    return ceil([self maxY]/maxPositiveLegendCount);
}

- (double)XLegendStep {
    double legendWidth = [[NSString stringWithFormat:@"%.2f", [self maxX]] sizeWithAttributes:self.legendFontAttributes].width + kMinHLegendSpacing;
    double maxLegendCount = [self chartWidth]/legendWidth + 1;
    return ceil([self maxX]/maxLegendCount);
}

#pragma mark - Lazy initialization

- (NSDictionary *)legendFontAttributes {
    if (!_legendFontAttributes) {
        UIFont *font = [UIFont systemFontOfSize:10.0];
        NSMutableParagraphStyle *style = [[NSMutableParagraphStyle alloc] init];
        [style setAlignment:NSTextAlignmentRight];
        _legendFontAttributes = @{
                                  NSFontAttributeName: font,
                                  NSParagraphStyleAttributeName:style,
                                  };
    }
    return _legendFontAttributes;
}

@end
