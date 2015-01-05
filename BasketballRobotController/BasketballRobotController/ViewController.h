//
//  ViewController.h
//  BasketballRobotController
//
//  Created by Maria Elena Villamil on 10/30/14.
//  Copyright (c) 2014 Maria Elena Villamil. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BLE.h"

@interface ViewController : UIViewController <BLEDelegate> {
    BLE* m_ble_endpoint;
}

@property UIColor* _green_color;

@property UIColor* _grey_color;

@property bool _can_set_height;

@property bool _bluetooth_connection;


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

@property (weak, nonatomic) IBOutlet UILabel *_ten_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_twenty_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_thirty_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_forty_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_fifty_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_sixty_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_seventy_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_eighty_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_ninety_cm_label;

@property (weak, nonatomic) IBOutlet UILabel *_hundred_cm_label;

//@property (weak, nonatomic) IBOutlet UILabel *_hundred_and_ten_cm_label;

//@property (weak, nonatomic) IBOutlet UILabel *_hundred_and_twenty_cm_label;

//@property (weak, nonatomic) IBOutlet UILabel *_hundred_and_thirty_cm_label;

//@property (weak, nonatomic) IBOutlet UILabel *_hundred_and_forty_cm_label;

//@property (weak, nonatomic) IBOutlet UILabel *_hundred_and_fifty_cm_label;

- (IBAction)onHeightSliderValueChange:(id)sender;

@end

