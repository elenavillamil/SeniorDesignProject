//
//  Project: BasketballRobotController
//  File: ViewController.m
//  Author: Maria Elena Villamil Rodriguez
//  Version: 1.0
//
//  Description: This file has the code to control the functionality of the application.
//  Notes: BLE related code was provided by Professor Eric Larson.
//


#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Setting member variables to its initial values
    self._status.text = @"Disconected";
    self._can_set_height = true;
    self._green_color = [UIColor colorWithRed:133.0/255.0 green:211.0/255.0
                                         blue:127.0/255.0 alpha:1];
    self._grey_color = [UIColor colorWithRed:188.0/255.0 green:188.0/255.0
                                        blue:188.0/255.0 alpha:1];
    
    self._can_set_height = false;
    self._bluetooth_connection = false;

    // Initializing the bluetooth.
    m_ble_endpoint = [[BLE alloc] init];
    [m_ble_endpoint controlSetup];

    // Set up the delegate to be this class.
    m_ble_endpoint.delegate = self;
    
    // Try to connect. This happens in a different thread.
    [self performSelectorInBackground:@selector(bleConnect:) withObject:nil];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void) bleDidConnect
{
    self._status.text = @"On";
    [self SetMainColors:(self._green_color)];
    
    self._bluetooth_connection = true;
    self._can_set_height = true;
    
}

-(void) bleDidDisconnect
{
    self._status.text = @"Disconnected.";
    [self SetMainColors:(self._grey_color)];
    [self SetLabelBackgroundOn:0];
    [self SetLabelBackgroundOff:0];
    self._bluetooth_connection = false;
    self._can_set_height = false;

    // Functionality to reconnect
    [self bleConnect:nil];
}

// Receiving and proccessing the Data
- (void) bleDidReceiveData:(unsigned char *)data length:(int)length
{
    NSData* input_data = [NSData dataWithBytes:data length:length];

    unsigned char dataBuffer[1] = { 0 };
    
    [input_data getBytes:dataBuffer length:sizeof(char) * 1];
    int height = dataBuffer[0];

    //NSLog(@"%i", height);

    // Setting the representation of the robot
    [self SetLabelBackgroundOn:height];
    [self SetLabelBackgroundOff:height];
    
    self._height.text = [[NSString alloc] initWithFormat:@"%d", height];
    
}

// Connecting to BRC (basketball robot controler) bluetooth.
- (void) bleConnect:(id) param
{
    self._status.text = @"Connecting...";
    
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

- (void) sliderChangedValue {
    if (self._can_set_height)
    {
        int current_value = self._height_slider.value;
        
        // Set the label that indicates the new heigth
        self._set_heigth_label.text = [[NSString alloc] initWithFormat:@"%d", current_value];
        
        // Getting the height in a byte so it can be send
        unsigned char height = (char)current_value;
        
        NSData* data_to_send = [NSData dataWithBytes:&height length: sizeof(char) * 1];
        
        //Sending the new slider value to the Arduino
        [m_ble_endpoint write:data_to_send];
        
    }
    else if (!self._bluetooth_connection)
    {
        // Making and showing pop up to let the user know it cannot use the application
        // until a connection is stablished.
        UIAlertView* alert_view = [[UIAlertView alloc] initWithTitle:@"Invalid action" message:@"There is not Bluetooth connection with the Robot, please wait until the connection is stablished." delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil, nil];
        [alert_view show];
        self._height_slider.value = [self._set_heigth_label.text intValue];
    }
    else
    {
        UIAlertView* alert_view = [[UIAlertView alloc] initWithTitle:@"Invalid action" message:@"The robot is in the proccess of reaching the last spcified height, please wait until the height is reached before setting a new height." delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil, nil];
        [alert_view show];
        self._height_slider.value = [self._set_heigth_label.text intValue];
    }

}
- (IBAction)onHeightSliderValueChangeOutside:(id)sender {
    [self sliderChangedValue];
}

- (IBAction)onHeightSliderValueChangeInside:(id)sender {
    [self sliderChangedValue];

}

- (IBAction)onOffButtonPressed:(id)sender {
    // Send 150 as new distnace to the robot.
    
    if ([[self._off_on_button titleForState:UIControlStateNormal ]  isEqual: @"Off" ])
    {
        self._status.text = @"Disconnected";
        self._bluetooth_connection = false;
        self._can_set_height = false;
    
        [self._off_on_button setBackgroundColor:[UIColor greenColor]];
        [self._off_on_button setTitle:@"On" forState:UIControlStateNormal];
        
        // Send off command to the arduino
        unsigned char to_send = (char)200;
        
        NSData* data_to_send = [NSData dataWithBytes:&to_send length: sizeof(char) * 1];
        
        //Sending the new slider value to the Arduino
        [m_ble_endpoint write:data_to_send];
        
        [self SetMainColors:(self._grey_color)];
        
    }
    else
    {
        if (!m_ble_endpoint.isConnected)
        {
            [self performSelectorInBackground:@selector(bleConnect:) withObject:nil];
        }
        
        self._status.text = @"Connected";
        self._bluetooth_connection = true;
        self._can_set_height = true;
        [self._off_on_button setBackgroundColor:[UIColor redColor]];
        [self._off_on_button setTitle:@"Off" forState:UIControlStateNormal];
        
        // Send off command to the arduino
        unsigned char to_send = (char)0;
        
        NSData* data_to_send = [NSData dataWithBytes:&to_send length: sizeof(char) * 1];
        
        //Sending the new slider value to the Arduino
        [m_ble_endpoint write:data_to_send];
        
        [self SetMainColors:(self._green_color)];

    }
}

// Set the colors of the labels and the slider to either grey or green.
// Grey if there app is connected to the robot, and green if there is no connection.
-(void) SetMainColors:(UIColor*)color
{
    
    self._velocity.backgroundColor = color;
    self._acceleration.backgroundColor = color;
    self._height.backgroundColor = color;
    self._status.backgroundColor = color;
    //self._direction.backgroundColor = color;
    self._acceleration_label.backgroundColor = color;
    //self._direction_label.backgroundColor = color;
    self._heigth_label.backgroundColor = color;
    self._velocity_label.backgroundColor = color;
    self._status_label.backgroundColor = color;
    self._height_slider.minimumTrackTintColor = color;
    self._height_slider.maximumTrackTintColor = color;
}

// Sets to green the height values that are smaller than the value passed in.
- (void) SetLabelBackgroundOn:(NSInteger)value
{
    if (value >= 5)
        self._five_cm_label.backgroundColor = self._green_color;
    
    if (value >= 10)
        self._ten_cm_label.backgroundColor = self._green_color;
    
    if (value >= 15)
        self._fifteen_cm_label.backgroundColor = self._green_color;
    
    if (value >= 20)
        self._twenty_cm_label.backgroundColor = self._green_color;
    
    if (value >= 25)
        self._twenty_five_cm_label.backgroundColor = self._green_color;
    
    if (value >= 30)
        self._thirty_cm_label.backgroundColor = self._green_color;
    
    if (value >= 35)
        self._thirty_five_cm_label.backgroundColor = self._green_color;
    
    if (value >= 40)
        self._fourty_cm_label.backgroundColor = self._green_color;
    
    if (value >= 45)
        self._fourty_five_cm_label.backgroundColor = self._green_color;
    
    if (value >= 50)
        self._fifty_cm_label.backgroundColor = self._green_color;
    
    if (value >= 55)
        self._fifty_five_cm_label.backgroundColor = self._green_color;
}

// Sets to white the height values that are bigger than the number passed in.
- (void) SetLabelBackgroundOff:(NSInteger)value
{
    /*
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
     */
    
    if (value < 55)
        self._fifty_five_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 50)
        self._fifty_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 45)
        self._fourty_five_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 40)
        self._fourty_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 35)
        self._thirty_five_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 30)
        self._thirty_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 25)
        self._twenty_five_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 20)
        self._twenty_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 15)
        self._fifteen_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 10)
        self._ten_cm_label.backgroundColor = [UIColor whiteColor];
    if (value < 5)
        self._five_cm_label.backgroundColor = [UIColor whiteColor];
}

@end






