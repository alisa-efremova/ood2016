//
//  CDChartTableViewCell.m
//  ChartDrawer
//
//  Created by Teploukhova, Alisa on 08/06/17.
//  Copyright © 2017 Teploukhova, Alisa. All rights reserved.
//

#import "CDChartTableViewCell.h"

@implementation CDChartTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    self.leftLabel.text = nil;
    self.rightLabel.text = nil;
}

- (void)prepareForReuse {
    [super prepareForReuse];
    self.leftLabel.text = nil;
    self.rightLabel.text = nil;
}


@end
