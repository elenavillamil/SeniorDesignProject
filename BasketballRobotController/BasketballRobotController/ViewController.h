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

@property (weak, nonatomic) IBOutlet UISlider *_height_slider;

@property (weak, nonatomic) IBOutlet UILabel *_set_heigth_label;

@property (weak, nonatomic) IBOutlet UILabel *_connection_label;

- (IBAction)onHeightSliderValueChange:(id)sender;

@end

