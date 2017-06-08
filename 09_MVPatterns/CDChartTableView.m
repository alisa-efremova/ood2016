//
//  CDChartTableView.m
//  ChartDrawer
//
//  Created by Teploukhova, Alisa on 08/06/17.
//  Copyright © 2017 Teploukhova, Alisa. All rights reserved.
//

#import "CDChartTableView.h"
#import "CDChartTableViewCell.h"

static NSString *const kCellReuseId = @"ChartCell";

@implementation CDChartTableView

- (void)awakeFromNib {
    [super awakeFromNib];

    [self registerNib:[UINib nibWithNibName:NSStringFromClass([CDChartTableViewCell class]) bundle:nil] forCellReuseIdentifier:kCellReuseId];
    self.delegate = self;
    self.dataSource = self;
    
    _step = 0.0;
}

#pragma mark - Setters

- (void)setStep:(double)step {
    _step = step;
    [self reloadData];
}

- (void)setValues:(NSArray<NSNumber *> *)values {
    _values = [values copy];
    [self reloadData];
}

#pragma mark - Table view data source methods

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.values count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    CDChartTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:kCellReuseId forIndexPath:indexPath];
    cell.leftLabel.text = [NSString stringWithFormat:@"%.6g", indexPath.row * self.step];
    cell.rightLabel.text = [NSString stringWithFormat:@"%.6g", [self.values[indexPath.row] doubleValue]];
    return cell;
}

#pragma mark - Table view delegate methods

static double kRowHeight = 30.0;

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return kRowHeight;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return kRowHeight;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section {
    double width = tableView.frame.size.width;
    double height = 18;
    double topPadding = 5;
    UIFont *font = [UIFont boldSystemFontOfSize:14];
    
    UIView *view = [[UIView alloc] initWithFrame:CGRectMake(0, 0, width, height)];
    view.backgroundColor = [UIColor colorWithRed:206/255.0 green:250/255.0 blue:250/255.0 alpha:1.0];
    
    UILabel *leftLabel = [[UILabel alloc] initWithFrame:CGRectMake(8, topPadding, width/2, height)];
    leftLabel.font = font;
    leftLabel.text = @"X";
    [view addSubview:leftLabel];
    
    UILabel *rightLabel = [[UILabel alloc] initWithFrame:CGRectMake(width/2, topPadding,width/2, height)];
    rightLabel.font = font;
    rightLabel.text = @"Y";
    [view addSubview:rightLabel];

    return view;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section {
    return CGFLOAT_MIN;
}

@end
