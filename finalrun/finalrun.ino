#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_BME280 bme; // I2C
Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

unsigned long delayTime;

// NeoPixel settings on the watch
#define LED_PIN    6    // Change to your NeoPixel data pin
#define NUMPIXELS  1     // Change if you have more than 1 NeoPixel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

const int VIBRATOR_PIN = 7; // Change the pin to your desired pin for the vibrator

bool vibrationTriggered = false;
unsigned long vibrationStartTime = 0;
bool ledOn = false;
unsigned long ledStartTime = 0;
float lastAccelX = 0.0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("BME280 and MPU6050 test"));

  pinMode(VIBRATOR_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  pixels.begin(); // Initialize NeoPixel
  pixels.show();  // Initialize all pixels to 'off'

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextSize(1.5);
  display.setTextColor(SSD1306_WHITE);
  displayWelcomeMessage();

  bool status;

  // Initialize BME sensor
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  // Initialize MPU6050
  Serial.println("Adafruit MPU6050 test!");

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  delayTime = 1000;
}

void loop() {
  display.setCursor(0, 0);
  display.clearDisplay();

  // Read BME sensor data
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;
  float humidity = bme.readHumidity();

  // Display BME sensor data on OLED
  display.print("Temp: "); display.print(temperature); display.println(" *C");
  display.print("Pres: "); display.print(pressure); display.println(" hPa");
  display.print("Humi: "); display.print(humidity); display.println(" %");

  // Read MPU6050 sensor data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Display MPU6050 sensor data on OLED
  display.print("Ax: "); display.print(a.acceleration.x); display.println(" m/s^2");
  display.print("Ay: "); display.print(a.acceleration.y); display.println(" m/s^2");
  //display.print("Gx: "); display.print(g.gyro.x); display.println(" rad/s");

  // Actuate based on conditions
  if (abs(a.acceleration.x) > 5.0 && !vibrationTriggered) {
    digitalWrite(VIBRATOR_PIN, HIGH);
    vibrationTriggered = true;
    vibrationStartTime = millis();
  }

  // Turn off the vibrator after 10 seconds
  if (vibrationTriggered && millis() > 20000) {
    digitalWrite(VIBRATOR_PIN, LOW);
     vibrationTriggered = false;
  }

  if (abs(a.acceleration.x - lastAccelX) >= 0.5) {
    digitalWrite(VIBRATOR_PIN, HIGH);
    delay(1000); // Vibrate for 1 second
    digitalWrite(VIBRATOR_PIN, LOW);
  }

  // Update lastAccelX
  lastAccelX = a.acceleration.x;

  // Actuate the NeoPixel based on temperature
  if (temperature > 25.0 && !ledOn) {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // Red
    ledOn = true;
    ledStartTime = millis();
  } else if (temperature > 20.0 && temperature <= 25.0 && !ledOn) {
    pixels.setPixelColor(0, pixels.Color(0, 255, 0)); // Green
    ledOn = true;
    ledStartTime = millis();
  } else if (temperature <= 20.0 && !ledOn) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // Blue
    ledOn = true;
    ledStartTime = millis();
  }

  // Turn off the LED after 10 seconds
  if (ledOn && millis() > 20000) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Turn off
    ledOn = false;
  }
  pixels.show(); // Send the updated color to the NeoPixel
  display.display();
  delay(delayTime);

   if (humidity > 39.0) {
    for (int i = 0; i < 5; ++i) {
      pixels.setPixelColor(0, pixels.Color(128, 0, 128)); // Purple
      pixels.show();
      delay(500);
      pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Off
      pixels.show();
      delay(500);
    }
  } 

  pixels.show(); // Send the updated color to the NeoPixel
  display.display();
  delay(delayTime);

}

  void displayWelcomeMessage() {
  // Display welcome message
  display.setTextSize(1);
  display.setCursor(20, 20);
  display.print("*");
  display.display();
  delay(2000); 
  display.print("Good Morning Laks");
  display.display();
  delay(5000);  // Display for 2 seconds
  display.clearDisplay();
  display.display();
}
