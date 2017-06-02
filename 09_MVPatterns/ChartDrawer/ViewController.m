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

@interface ViewController () <UITableViewDelegate, UITableViewDataSource>
@property (nonatomic) NSMutableArray<CDHarmonicFunction *> *harmonics;
@property (nonatomic) IBOutlet UITableView *tableView;
@property (weak, nonatomic) IBOutlet UIImageView *graphImageView;
@end

static NSString *const kCellReuseIdentifier = @"Cell";

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    _harmonics = [NSMutableArray arrayWithObject:[[CDHarmonicFunction alloc] initWithFunctionType:CDFunctionTypeSin amplitude:4.38 frequency:2.25 phase:1.5]];
    
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:kCellReuseIdentifier];
    [self updateGraph];
}

- (void)updateGraph {
    unsigned size = 100;
    double values[size];
    double step = 0.05;
    for (int i = 0; i < size; i++) {
        values[i] = 0;
        for (CDHarmonicFunction *function in self.harmonics) {
            values[i] += [function valueWithX:(i*step)];
        }
    }
    [self drawGraphWithStep:step values:values size:size];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    UINavigationController *navigationVC = (UINavigationController *)[segue destinationViewController];
    HarmonicViewController *vc = (HarmonicViewController *)[navigationVC topViewController];
    if ([segue.identifier isEqualToString:@"CreateFunctionSeque"]) {
        vc.completionBlock = ^(CDHarmonicFunction *function) {
            if (function) {
                [self.harmonics addObject:function];
                [self.tableView reloadData];
                [self updateGraph];
            }
        };
    } else if ([segue.identifier isEqualToString:@"EditFunctionSeque"]) {
        NSInteger selectedIndex = [self.tableView indexPathForSelectedRow].row;
        CDHarmonicFunction *edittingFunction = self.harmonics[selectedIndex];
        vc.function = edittingFunction;
        vc.completionBlock = ^(CDHarmonicFunction *function) {
            if (function) {
                edittingFunction.amplitude = function.amplitude;
                edittingFunction.functionType = function.functionType;
                edittingFunction.frequency = function.frequency;
                edittingFunction.phase = function.phase;
                [self.tableView reloadData];
                [self updateGraph];
            }
        };
    }
}

- (IBAction)addHarmonicAction:(UIBarButtonItem *)sender {
    HarmonicViewController *vc = [[HarmonicViewController alloc] initWithFunction:nil completion:^(CDHarmonicFunction *function) {
        [self.harmonics addObject:function];
    }];
    UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:vc];
    navigationController.modalPresentationStyle = UIModalPresentationFormSheet;
    
    [self.navigationController presentViewController:navigationController animated:YES completion:nil];
}


#pragma mark - Table view data source methods

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.harmonics count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:kCellReuseIdentifier forIndexPath:indexPath];
    CDHarmonicFunction *function = self.harmonics[indexPath.row];
    cell.textLabel.text = [NSString stringWithFormat:@"%@", function];
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    return cell;
}

#pragma mark - Table view delegate methods

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    return YES;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [self performSegueWithIdentifier:@"EditFunctionSeque" sender:self];
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        [self.harmonics removeObjectAtIndex:indexPath.row];
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationAutomatic];
        [self updateGraph];
    }
}

#pragma mark - Drawing

- (void)drawGraphWithStep:(double)step values:(double[])values size:(int)size {
    double width = self.graphImageView.bounds.size.width;
    double height = self.graphImageView.bounds.size.height;
    
    UIGraphicsBeginImageContextWithOptions(CGSizeMake(width, height), NO, 0);
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    // draw legend
    CGContextSetLineWidth(context, 1.0);
    CGContextSetStrokeColorWithColor(context, [UIColor lightGrayColor].CGColor);
    CGContextMoveToPoint(context, 0, 0);
    CGContextAddLineToPoint(context, 0, height);
    CGContextMoveToPoint(context, 0, height/2);
    CGContextAddLineToPoint(context, width, height/2);
    CGContextStrokePath(context);
    
    // find max Y
    double maxY = 0;
    for (int i = 0; i < size; i++) {
        double tmp = values[i] < 0 ? -values[i] : values[i];
        maxY = MAX(maxY, tmp);
    }
    
    CGContextSetStrokeColorWithColor(context, [UIColor blueColor].CGColor);
    CGContextMoveToPoint(context, 0, height/2 - values[0]*height/2/maxY);
    for (int i = 1; i < size; i++) {
        double realX = i*step;
        double realY = values[i];
        double scaledX = realX*width/size/step;
        double scaledY = height/2 - realY*height/2/maxY;
        CGContextAddLineToPoint(context, scaledX, scaledY);
    }

    CGContextStrokePath(context);
    UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    self.graphImageView.image = img;
}

@end
