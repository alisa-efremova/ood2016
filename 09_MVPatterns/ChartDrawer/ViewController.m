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
@end

static NSString *const kCellReuseIdentifier = @"Cell";

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    _harmonics = [NSMutableArray arrayWithObject:[[CDHarmonicFunction alloc] initWithFunctionType:CDFunctionTypeSin amplitude:4.2 frequency:10 phase:2]];
    
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:kCellReuseIdentifier];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    NSLog(@"segue:%@", segue.identifier);
    UINavigationController *navigationVC = (UINavigationController *)[segue destinationViewController];
    HarmonicViewController *vc = (HarmonicViewController *)[navigationVC topViewController];
    if ([segue.identifier isEqualToString:@"CreateFunctionSeque"]) {
        vc.completionBlock = ^(CDHarmonicFunction *function) {
            if (function) {
                [self.harmonics addObject:function];
                [self.tableView reloadData];
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
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        [self.harmonics removeObjectAtIndex:indexPath.row];
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationAutomatic];
    }
}

@end
