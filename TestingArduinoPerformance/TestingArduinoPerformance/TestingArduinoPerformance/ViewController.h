//
//  ViewController.h
//  TestingArduinoPerformance
//
//  Created by Maria Elena Villamil on 11/24/14.
//  Copyright (c) 2014 Maria Elena Villamil. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BLE.h"

@interface ViewController : UIViewController <BLEDelegate> {
    BLE* m_ble_endpoint;
}

@property (weak, nonatomic) IBOutlet UILabel *_info_label;

@property (weak, nonatomic) IBOutlet UILabel *_distance_label;
@property (weak, nonatomic) IBOutlet UILabel *_slider_value;
@property (weak, nonatomic) IBOutlet UISlider *_slider;
- (IBAction)_on_height_change:(id)sender;

@end

