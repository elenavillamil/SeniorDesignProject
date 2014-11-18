//
//  ViewController.m
//  BasketballRobotController
//
//  Created by Maria Elena Villamil on 10/30/14.
//  Copyright (c) 2014 Maria Elena Villamil. All rights reserved.
//


//
//  ViewController.m
//  DistanceAppM
//
//  Created by Cheong on 15/8/12.
//  Modified by Eric Larson, 2014
//  Modified by Maria Elena Villamil, 2014
//  Copyright (c) 2014 Maria Elena Villamil. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

@synthesize _connection_label;
@synthesize _height_slider;
@synthesize _set_heigth_label;
@synthesize _ten_cm_label;
@synthesize _twenty_cm_label;
@synthesize _thirty_cm_label;
@synthesize _forty_cm_label;
@synthesize _fifty_cm_label;
@synthesize _sixty_cm_label;
@synthesize _seventy_cm_label;
@synthesize _eighty_cm_label;
@synthesize _ninety_cm_label;
@synthesize _hundred_cm_label;
@synthesize _hundred_and_ten_cm_label;
@synthesize _hundred_and_twenty_cm_label;
@synthesize _hundred_and_thirty_cm_label;
@synthesize _hundred_and_forty_cm_label;
@synthesize _hundred_and_fifty_cm_label;
@synthesize _acceleration_label;
@synthesize _direction_label;
@synthesize _heigth_label;
@synthesize _status_label;
@synthesize _velocity_label;

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self._connection_label.text = @"";
    
    self._green_color = [UIColor colorWithRed:133.0/255.0 green:211.0/255.0 blue:127.0/255.0 alpha:1];
    
    self._can_set_height = false;
    
    //m_ble_endpoint = [[BLE alloc] init];
    //[m_ble_endpoint controlSetup];
    
    // Set up the delegate to be this class.
    //m_ble_endpoint.delegate = self;
    
    // Try to connect. In a different thread.
    //[self performSelectorInBackground:@selector(bleConnect:) withObject:nil];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void) bleDidConnect
{
    self._connection_label.text = @"";
    self._status_label.text = @"On";
    self._can_set_height = true;
    [self SetMainColors:(self._green_color)];
}

-(void) bleDidDisconnect
{
    self._connection_label.text = @"Disconnected.";
    self._status_label.text = @"Disconnected.";
    [self SetMainColors:(self._grey_color)];
    
    // Functionality to reconnect
    [self bleConnect:nil];
}

// Receiving and proccessing the Data
- (void) bleDidReceiveData:(unsigned char *)data length:(int)length
{
    NSData* input_data = [NSData dataWithBytes:data length:length];
    NSString* parsed_str = [[NSString alloc] initWithData:input_data encoding:NSUTF8StringEncoding];
    
    // Debug log
    NSLog(@"%@", parsed_str);
    
    NSNumberFormatter* formatter = [[NSNumberFormatter alloc] init];
    [formatter setNumberStyle:NSNumberFormatterDecimalStyle];
    NSNumber* distance = [formatter numberFromString:parsed_str];
    
    // Setting the representation of the robot
    [self SetLabelBackgroundOn:distance.intValue];
    [self SetLabelBackgroundOff:distance.integerValue];
}

// Connecting to BRC (basketball robot controler) bluetooth.
- (void) bleConnect:(id) param
{
    self._connection_label.text = @"Connecting Please Wait...";
    
    [NSThread sleepForTimeInterval:.5f];
    
    //start search for peripherals with a timeout of 3 seconds
    // this is an asunchronous call and will return before search is complete
    [m_ble_endpoint findBLEPeripherals:3];
    
    // Sleep the three seconds
    [NSThread sleepForTimeInterval:3.0f];
    
    if(m_ble_endpoint.peripherals.count > 0)
    {
        // connect to the first found peripheral
        
        for(int i = 0; i < m_ble_endpoint.peripherals.count; ++i)
        {
            CBPeripheral* peripheral = [m_ble_endpoint.peripherals objectAtIndex:i];
            
            if ([peripheral.name isEqualToString:@"BRC"])
            {
                [m_ble_endpoint connectPeripheral:[m_ble_endpoint.peripherals objectAtIndex:i]];
            }
        }
        
    }
}

- (IBAction)onHeightSliderValueChange:(id)sender {
    
    if (self._can_set_height)
    {
        int current_value = self._height_slider.value;
        NSNumber* ns_current_value = [[NSNumber alloc] initWithInt:current_value];
        
        // Set the label that indicates the ehigth
        
        self._set_heigth_label.text = [[NSString alloc] initWithFormat:@"%d", current_value];
        
        //Sending the new slider value to the Arduino
        //NSString* value_string = [NSString stringWithFormat:@"New Height: %d", current_value];
        //value_string = [NSString stringWithFormat:@"%@\r\n", value_string];
        //NSData* data_to_send = [value_string dataUsingEncoding:NSUTF8StringEncoding];
        //self._set_heigth_label.text = value_string;
        //[m_ble_endpoint write:data_to_send];
        
    }
    
    // else pop up with options.
}

-(void) SetMainColors:(UIColor*)color
{
    self._velocity.backgroundColor = color;
    self._acceleration.backgroundColor = color;
    self._height.backgroundColor = color;
    self._status.backgroundColor = color;
    self._direction.backgroundColor = color;
    self._acceleration_label.backgroundColor = color;
    self._direction_label.backgroundColor = color;
    self._heigth_label.backgroundColor = color;
    self._velocity_label.backgroundColor = color;
    self._status_label.backgroundColor = color;
    self._height_slider.minimumTrackTintColor = color;
    self._height_slider.maximumTrackTintColor = color;
}

- (void) SetLabelBackgroundOn:(int)value
{
    if (value >= 10)
        self._ten_cm_label.backgroundColor = self._green_color;
    
    if (value >= 20)
        self._twenty_cm_label.backgroundColor = self._green_color;
    
    if (value >= 30)
        self._thirty_cm_label.backgroundColor = self._green_color;
    
    if (value >= 40)
        self._forty_cm_label.backgroundColor = self._green_color;
    
    if (value >= 50)
        self._fifty_cm_label.backgroundColor = self._green_color;
    
    if (value >= 60)
        self._sixty_cm_label.backgroundColor = self._green_color;
    
    if (value >= 70)
        self._seventy_cm_label.backgroundColor = self._green_color;
    
    if (value >= 80)
        self._eighty_cm_label.backgroundColor = self._green_color;
    
    if (value >= 90)
        self._ninety_cm_label.backgroundColor = self._green_color;
    
    if (value >= 100)
        self._hundred_cm_label.backgroundColor = self._green_color;
    
    if (value >= 110)
        self._hundred_and_ten_cm_label.backgroundColor = self._green_color;
    
    if (value >= 120)
        self._hundred_and_twenty_cm_label.backgroundColor = self._green_color;
    
    if (value >= 130)
        self._hundred_and_thirty_cm_label.backgroundColor = self._green_color;
    
    if (value >= 140)
        self._hundred_and_forty_cm_label.backgroundColor = self._green_color;
    
    if (value >= 150)
        self._hundred_and_fifty_cm_label.backgroundColor = self._green_color;
}

- (void) SetLabelBackgroundOff:(int)value
{
    if (value < 150)
        self._hundred_and_fifty_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 140)
        self._hundred_and_forty_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 130)
        self._hundred_and_thirty_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 120)
        self._hundred_and_twenty_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 110)
        self._hundred_and_ten_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 100)
        self._hundred_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 90)
        self._ninety_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 80)
        self._eighty_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 70)
        self._seventy_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 60)
        self._sixty_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 50)
        self._fifty_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 40)
        self._forty_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 30)
        self._thirty_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 20)
        self._twenty_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 10)
        self._ten_cm_label.backgroundColor = [UIColor whiteColor];
}

- (IBAction)Connect:(id)sender {
}
@end






