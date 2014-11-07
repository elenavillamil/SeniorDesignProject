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

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self._connection_label.text = @"Connecting...";
    
    m_ble_endpoint = [[BLE alloc] init];
    [m_ble_endpoint controlSetup];
    
    // Set up the delegate to be this class.
    m_ble_endpoint.delegate = self;
    
    // Try to connect. In a different thread.
    [self performSelectorInBackground:@selector(bleConnect:) withObject:nil];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void) bleDidConnect
{
    self._connection_label.text = @"";
}

-(void) bleDidDisconnect
{
    self._connection_label.text = @"Disconnected.";
    
    // Functionality to reconnect
    [self bleConnect:nil];
}

// Receiving and proccessing the Data
- (void) bleDidReceiveData:(unsigned char *)data length:(int)length
{
    
}

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
    int current_value = self._height_slider.value;
    NSString* value_string = [NSString stringWithFormat:@"%d", current_value];
    value_string = [NSString stringWithFormat:@"%@\r\n", value_string];
    NSData* data_to_send = [value_string dataUsingEncoding:NSUTF8StringEncoding];
    self._set_heigth_label.text = value_string;
    
    [m_ble_endpoint write:data_to_send];
    
}


- (IBAction)Connect:(id)sender {
}
@end





