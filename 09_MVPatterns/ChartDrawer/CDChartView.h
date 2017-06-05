//
//  CDChartView.h
//  ChartDrawer
//
//  Created by Teploukhova, Alisa on 05/06/17.
//  Copyright © 2017 Teploukhova, Alisa. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CDChartView : UIView
@property (nonatomic) double step;
@property (nonatomic, copy) NSArray<NSNumber *> *values;
@end
