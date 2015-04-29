//
//  ViewController.h
//  BasketballRobotController
//
//  Created by Maria Elena Villamil on 10/30/14.
//  Copyright (c) 2014 Maria Elena Villamil. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "JBLineChartView.h"

#import "BLE.h"

@interface ViewController : UIViewController <BLEDelegate, JBLineChartViewDataSource, JBLineChartViewDelegate> {
    BLE* m_ble_endpoint;
}

@property UIColor* _green_color;

@property UIColor* _grey_color;

@property bool _can_set_height;

@property bool _bluetooth_connection;


@property (weak, nonatomic) IBOutlet UIButton *_off_on_button;

@property (weak, nonatomic) IBOutlet UISlider *_height_slider;

@property (weak, nonatomic) IBOutlet UILabel *_set_heigth_label;

@property (weak, nonatomic) IBOutlet UILabel *_status_label;

@property (weak, nonatomic) IBOutlet UILabel *_heigth_label;

@property (weak, nonatomic) IBOutlet UILabel *_velocity_label;

@property (weak, nonatomic) IBOutlet UILabel *_acceleration_label;

@property (weak, nonatomic) IBOutlet UILabel *_status;

@property (weak, nonatomic) IBOutlet UILabel *_height;

@property (weak, nonatomic) IBOutlet UILabel *_velocity;

@property (weak, nonatomic) IBOutlet UILabel *_acceleration;

@property (weak, nonatomic) IBOutlet UILabel *_connection_label;

@property (weak, nonatomic) IBOutlet UILabel *_three_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_six_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_nine_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_twelve_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_fiftheen_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_eighteen_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_twenty_first_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_twenty_four_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_twenty_seven_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_thirty_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_thirty_three_cm_label;
@property (weak, nonatomic) IBOutlet UILabel *_thirty_six_cm_label;
@property (weak, nonatomic) IBOutlet UILabel *_thirty_nine_cm_label;
@property (weak, nonatomic) IBOutlet UILabel *_fourty_two_cm_label;
@property (weak, nonatomic) IBOutlet UILabel *_fourty_five_cm_label;
@property (weak, nonatomic) IBOutlet UILabel *_fourty_eight_cm_label;
@property (weak, nonatomic) IBOutlet UILabel *_fifty_one_cm_label;

@property (retain, nonatomic) NSMutableArray* heights;

@property (weak, nonatomic) IBOutlet JBLineChartView *_graph;
@property (weak, nonatomic) IBOutlet UIButton *_show_graph_button;

- (void)sliderChangedValue;
- (IBAction)showGraph:(id)sender;

- (IBAction)onOffButtonPressed:(id)sender;
- (IBAction)onHeightSliderValueChangeOutside:(id)sender;
- (IBAction)onHeightSliderValueChangeInside:(id)sender;

@end

