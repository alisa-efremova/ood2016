//
//  HarmonicViewController.m
//  ChartDrawer
//
//  Created by Teploukhova, Alisa on 01/06/17.
//  Copyright © 2017 Teploukhova, Alisa. All rights reserved.
//

#import "HarmonicViewController.h"

@interface HarmonicViewController ()
@property (nonatomic) IBOutlet UITextField *amplitudeTextField;
@property (nonatomic) IBOutlet UITextField *frequencyTextField;
@property (nonatomic) IBOutlet UITextField *phaseTextField;
@property (nonatomic) IBOutlet UISegmentedControl *functionTypeSwitcher;
@property (nonatomic) CDFunctionType functionType;

@end

@implementation HarmonicViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    if (!self.function) {
        self.function = [[CDHarmonicFunction alloc] init];
    }
    [self displayFunction];
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _function = [[CDHarmonicFunction alloc] init];
    }
    return self;
}

- (instancetype)initWithFunction:(CDHarmonicFunction *)function completion:(void (^)(CDHarmonicFunction *function))completion {
    self = [super init];
    if (self) {
        _function = function ? function : [[CDHarmonicFunction alloc] init];
        _completionBlock = completion;
    }
    return self;
}

- (void)setFunction:(CDHarmonicFunction *)function {
    _function = function;
    [self displayFunction];
}

#pragma mark - Actions

- (IBAction)cancelButtonAction:(UIBarButtonItem *)sender {
    [self.navigationController dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)doneButtonAction:(UIBarButtonItem *)sender {
    [self.navigationController dismissViewControllerAnimated:YES completion:^{
        if (self.completionBlock) {
            self.function.amplitude = [self.amplitudeTextField.text doubleValue];
            self.function.frequency = [self.frequencyTextField.text doubleValue];
            self.function.phase = [self.phaseTextField.text doubleValue];
            self.function.functionType = self.functionTypeSwitcher.selectedSegmentIndex;
            self.completionBlock(self.function);
        }
    }];
}

- (IBAction)functionTypeChanged:(UISegmentedControl *)sender {
    self.functionType = self.functionTypeSwitcher.selectedSegmentIndex;
}

#pragma mark - Helpers

- (NSString *)doubleToString:(double)val {
    return [NSString stringWithFormat:@"%g", val];
}

- (void)displayFunction {
    if (self.function) {
        self.amplitudeTextField.text = [self doubleToString:self.function.amplitude];
        self.frequencyTextField.text = [self doubleToString:self.function.frequency];
        self.phaseTextField.text = [self doubleToString:self.function.phase];
        self.functionTypeSwitcher.selectedSegmentIndex = self.function.functionType;
    }
}

@end
