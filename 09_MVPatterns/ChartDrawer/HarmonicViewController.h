//
//  HarmonicViewController.h
//  ChartDrawer
//
//  Created by Teploukhova, Alisa on 01/06/17.
//  Copyright © 2017 Teploukhova, Alisa. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CDHarmonicFunction.h"

@interface HarmonicViewController : UIViewController
@property (nonatomic) CDHarmonicFunction *function;
@property (nonatomic, copy) void (^completionBlock)(CDHarmonicFunction *function);
@end
