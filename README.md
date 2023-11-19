# 📦 Automated Order Fulfillment System with RFID Integration

## 📋 Table of Contents

- [🚀 Introduction](#-introduction)
- [✨ Features](#-features)
- [🛠️ Technologies Used](#%EF%B8%8F-technologies-used)
- [⚙️ Installation](#%EF%B8%8F-installation)
- [🔧 Usage](#-usage)
- [🏗️ Architecture](#%EF%B8%8F-architecture)
- [👥 Project Team](#-project-team)
- [🤝 Contributing](#-contributing)
- [📝 License](#-license)

## 🚀 Introduction

The Automated Order Fulfillment System with RFID Integration is a sophisticated system designed to automate the process of fulfilling user orders placed via a web interface. This system harmonizes a Python-based application and an Arduino-based bot equipped with an RFID reader to efficiently pick and deliver items from an inventory.

Upon order placement through the web interface, each item within an order is linked to a unique RFID code. The Python application continuously monitors the MySQL database for new orders. When a new order is detected, the Python application triggers the Arduino bot, which navigates through inventory shelves, identifies items based on RFID matches, picks them up, and delivers them to a specified location for user pickup.

## ✨ Features

- **Order Monitoring**: Constantly checks the MySQL database for new user orders.
- **Arduino Bot Control**: Activates and controls the Arduino bot for order fulfillment based on database updates.
- **RFID Integration**: Utilizes RFID technology for matching order items with the physical inventory for precise item retrieval.
- **Automated Item Picking**: Guides the bot through shelf navigation, reads RFID tags, and autonomously picks and delivers items.

## 🛠️ Technologies Used

The project harnesses the power of the following technologies:

- **Python**: For database monitoring and orchestrating order fulfillment.
- **MySQL**: Database management system for storing order details and item information.
- **Arduino**: Microcontroller-based system controlling bot movements and actions.
- **Raspberry Pi**: Mini computer, can ber replaced by any PC if it can be placed on bot.
- **RFID (MFRC522) Module**: Allows the Arduino bot to read RFID tags associated with items.
- **Serial Communication**: Facilitates communication between Python and Arduino systems.
- **Servo Motor Control**: Manages the bot's picking mechanism movement.
- **Vercel**: Front-end deployed on Vercel app.

## ⚙️ Installation

To set up and run this project locally, follow these steps:

0. **Build the bot**: 
   - It must be able to go staright and reverse, has RFID reader on the bottom, has some kind of arm and storage to pick and carry items and has to facilitate enough space for Raspberry Pi, Arduino and batteries.
1. **Clone the repository**: `git clone https://github.com/your-username/order-fulfillment.git`
2. **Front end side**:
   - The front-end for this project has been developed and deployed. You can find detailed instructions and information about the front-end deployment in this repository: [Front-end Repository](https://github.com/muradtaghiyev05/pam-project). Please follow the instructions provided in the front-end repository for setting up, deploying, and using the front-end interface of this system. After deployment you can set custom URL to your site. 
   - (OPTIONAL) You can develop your own front-end, connect it to any database, make required changes to `main.py` depending on this database and deploy the site.
3. **Configure database credentials**:
   - Update the `CREDENTIALS` dictionary in the Python script with your database details.
4. **Install necessary dependencies on Raspberry Pi and your Machine**:
   - Python packages - Raspberryy Pi: `pip install -r requirements.txt`
   - Arduino libraries - Your Machine/Raspberry Pi: Refer to the list of libraries used in the Arduino sketch and install them using the Arduino IDE's Library Manager.
5. **Connect the Arduino**:
   - Connect it to the specified port (change `PORT` variable if necessary) and upload the Arduino sketch to the board.
6. **Upload Python code (`main.py`) to Raspberry Pi**
   - Uplad the code make sure the `PORT` variable is configured correcly again once again.

## 🔧 Usage

1. Users place orders via the website [https://pam-project.vercel.app/](https://shopbot-site.vercel.app) associating each item with a unique RFID code.
   (URL could be anything you set, for more info see : [⚙️ Installation](#installation) - 3)
3. Run the Python script `main.py` to start monitoring the database for new orders.
4. Upon detecting new orders, the Python script triggers the Arduino bot, which navigates shelves and picks items based on RFID matches.
5. The bot delivers the items to the designated location for user pickup.

## 🏗️ Architecture

### Database Schema

- **`Orders` Table**: Stores order information, including order ID, date, and item-RFID associations.

### Workflow

1. User places an order via the website, associating each item with an RFID code.
2. Python application continuously monitors the `Orders` table for new orders.
3. Upon detecting a new order, Python triggers the Arduino bot.
4. The Arduino bot navigates shelves, reads RFID tags, and picks corresponding items.
5. Items are delivered to the designated location for user pickup.

## 👥 Project Team

- **Supervisor (BHOS Lecturer - Robotics)** : [Aydin Nasirzade](https://github.com/supervisor)
- **Hardware (Arduino - Sensors)**: [Arif Najafov](https://github.com/hardware-lead)
- **Hardware Assistant (Construction - Mechanics)**: [Nijat Aliyev](https://github.com/nicataie)
- **Sofware (Arduino - Python)**: [Elshad Sabziyev](https://github.com/sabziyevelshad)
- **Front-end Developer**: [Murad Taghiyev](https://github.com/muradtaghiyev05)
- **AI/ML Expert (Planned for future development)**: [Gurban Guliyev](https://github.com/QuriMAY)

## 🛣️ Roadmap

### 🚀 Version 1.0.0 (Current Release)

- **Basic Order Fulfillment**:
  - Implement basic functionality to monitor orders and automate item picking based on RFID matches.
  - Database integration for storing orders and item details.

### 🚀 Version 1.1.0 (Upcoming Release)

- **🎨 Enhanced User Interface**:
  - Refine front-end design for a more intuitive user experience.
  - Add visual indicators for order statuses and item picking progress.

- **🔐 QR Code Token Generation for Pickup Verification**:
  - Generate unique QR code tokens for each order placed, containing the site URL and a special token.
  - Allow customers to access their unique QR codes through the order confirmation page for in-store pickup verification.

### 🚀 Version 1.2.0

- **📡 Additional RFID Support**:
  - Expand RFID support for different tag types or frequencies.
  - Improve RFID reading accuracy and speed.

### 🚀 Future Enhancements

- **🤖 AI/ML Integration**:
  - Investigate the possibility of implementing AI/ML algorithms for predictive inventory management and optimization.
  - Explore machine learning for enhanced decision-making in item picking.

- **📲 Real-time Notifications**:
  - Implement real-time notifications for users regarding order status updates, such as item picked, ready for pickup, etc.

- **📱 Multi-platform Support**:
  - Extend the system to support multiple platforms (mobile app compatibility, other web frameworks).

- **⚙️ Scalability and Performance**:
  - Optimize codebase and infrastructure to handle larger inventories and increased user loads efficiently.

- **🗣️ Community Feedback**:
  - Gather feedback from users and contributors to prioritize and implement requested features or improvements.

Please note that the roadmap is subject to change based on project requirements, feedback, and emerging priorities.


## 🤝 Contributing

Contributions to improve functionality or add new features are welcome! To contribute:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature/your-feature`
3. Make changes and commit: `git commit -m 'Add your feature'`
4. Push to the branch: `git push origin feature/your-feature`
5. Submit a pull request.

## 📝 License

This project is licensed under the [GNU GPLv3 License](LICENSE).
