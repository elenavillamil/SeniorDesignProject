//
//  ViewController.m
//  TestingArduinoPerformance
//
//  Created by Maria Elena Villamil on 11/24/14.
//  Copyright (c) 2014 Maria Elena Villamil. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    m_ble_endpoint = [[BLE alloc] init];
    [m_ble_endpoint controlSetup];
    
    // Set up the delegate to be this class.
    m_ble_endpoint.delegate = self;
    
    // Try to connect. In a different thread.
    [self performSelectorInBackground:@selector(bleConnect:) withObject:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void) bleDidConnect
{
    self._info_label.text = @"";
    
}

-(void) bleDidDisconnect
{
    self._info_label.text = @"Disconnected.";
    
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
    
    //NSNumberFormatter* formatter = [[NSNumberFormatter alloc] init];
    //[formatter setNumberStyle:NSNumberFormatterDecimalStyle];
    //NSNumber* distance = [formatter numberFromString:parsed_str];
    
    self._distance_label.text = parsed_str;
}


// Connecting to BRC (basketball robot controler) bluetooth.
- (void) bleConnect:(id) param
{
    self._info_label.text = @"Connecting Please Wait...";
    
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
            
            if ([peripheral.name isEqualToString:@"ev9"])
            {
                [m_ble_endpoint connectPeripheral:[m_ble_endpoint.peripherals objectAtIndex:i]];
            }
        }
        
    }
}


- (IBAction)_on_height_change:(id)sender {
    
    int current_value = self._slider.value;
    
    // Preparing data to be send
    NSString* value_string = [NSString stringWithFormat:@"%d", current_value];
//    NSNumber* value = [NSNumber numberWithInt:current_value];
//    value_string = [NSString stringWithFormat:@"%@\r\n", value_string];
    NSData* data_to_send = [NSData dataWithBytes:&current_value length: 1];
    
    // Updating label with the new value
    self._distance_label.text = value_string;
    
    // Sending the new slider value to the Arduino
    [m_ble_endpoint write:data_to_send];

}
@end
