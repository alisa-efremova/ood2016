//
//  CDChartTableView.h
//  ChartDrawer
//
//  Created by Teploukhova, Alisa on 08/06/17.
//  Copyright © 2017 Teploukhova, Alisa. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface CDChartTableView : UITableView<UITableViewDelegate, UITableViewDataSource>
@property (nonatomic) double step;
@property (nonatomic, copy) NSArray<NSNumber *> *values;
@end
