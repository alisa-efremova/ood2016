//
//  ViewController.m
//  ChartDrawer
//
//  Created by Teploukhova, Alisa on 01/06/17.
//  Copyright © 2017 Teploukhova, Alisa. All rights reserved.
//

#import "ViewController.h"
#import "CDHarmonicFunction.h"
#import "HarmonicViewController.h"
#import "CDChartView.h"
#import "CDChartTableView.h"

@interface ViewController () <UITableViewDelegate, UITableViewDataSource>
@property (nonatomic) NSMutableArray<CDHarmonicFunction *> *functions;
@property (nonatomic) IBOutlet UITableView *tableView;
@property (nonatomic) IBOutlet CDChartView *chartView;
@property (nonatomic) IBOutlet CDChartTableView *chartTableView;
@end

static NSString *const kCellReuseId = @"Cell";
static NSString *const kCreateFunctionSequeId = @"CreateFunctionSeque";
static NSString *const kEditFunctionSequeId = @"EditFunctionSeque";

static double kStep = 0.05;
static NSUInteger kPointsCount = 100;

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:kCellReuseId];
    
    self.functions = [NSMutableArray arrayWithObject:[[CDHarmonicFunction alloc] initWithFunctionType:CDFunctionTypeSin amplitude:4.38 frequency:2.25 phase:1.5]];
    
    self.chartView.step = kStep;
    self.chartTableView.step = kStep;
    [self recalculateChartData];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    UINavigationController *navigationVC = (UINavigationController *)[segue destinationViewController];
    HarmonicViewController *vc = (HarmonicViewController *)[navigationVC topViewController];
    if ([segue.identifier isEqualToString:kCreateFunctionSequeId]) {
        vc.completionBlock = ^(CDHarmonicFunction *function) {
            if (function) {
                [self.functions addObject:function];
                [self.tableView reloadData];
                [self recalculateChartData];
            }
        };
    } else if ([segue.identifier isEqualToString:kEditFunctionSequeId]) {
        NSInteger selectedIndex = [self.tableView indexPathForSelectedRow].row;
        CDHarmonicFunction *edittingFunction = self.functions[selectedIndex];
        vc.function = edittingFunction;
        vc.completionBlock = ^(CDHarmonicFunction *function) {
            if (function) {
                edittingFunction.amplitude = function.amplitude;
                edittingFunction.type = function.type;
                edittingFunction.frequency = function.frequency;
                edittingFunction.phase = function.phase;
                [self.tableView reloadData];
                [self recalculateChartData];
            }
        };
    }
}

- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator {
    [self.chartView setNeedsDisplay];
}

#pragma mark - Table view data source methods

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.functions count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:kCellReuseId forIndexPath:indexPath];
    cell.textLabel.text = [NSString stringWithFormat:@"%@", self.functions[indexPath.row]];
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    return cell;
}

#pragma mark - Table view delegate methods

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    return YES;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [self performSegueWithIdentifier:kEditFunctionSequeId sender:self];
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        [self.functions removeObjectAtIndex:indexPath.row];
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationAutomatic];
        [self recalculateChartData];
    }
}

#pragma mark - Actions

- (IBAction)changeChartView:(UISegmentedControl *)sender {
    if (sender.selectedSegmentIndex == 0) {
        self.chartView.hidden = NO;
        self.chartTableView.hidden = YES;
    } else {
        self.chartView.hidden = YES;
        self.chartTableView.hidden = NO;
    }
}

#pragma mark - Helpers

- (void)recalculateChartData {
    NSMutableArray<NSNumber *> *values = [NSMutableArray array];
    for (int i = 0; i < kPointsCount; i++) {
        double sum = 0;
        for (CDHarmonicFunction *function in self.functions) {
            sum += [function valueWithX:(i * kStep)];
        }
        values[i] = [NSNumber numberWithDouble:sum];
    }
    self.chartView.values = values;
    self.chartTableView.values = values;
}

@end
