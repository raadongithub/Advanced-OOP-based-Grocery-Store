Admin Password: Raad
# Advanced Console-Based  C++ Store Using OOP

## Overview
The Advanced Console-Based C++ Store project is an enhancement of a previous sparse project, implementing Object-Oriented Programming (OOP) principles to improve code structure, maintainability, and efficiency. This console application simulates a real-world shopping experience, providing functionalities such as product browsing, selection, cart management, customer details handling, and an advanced admin interface for product management.

## Repository Contents
- `main.cpp`: The main source code file containing the implementation of the Advanced Console-Based C++ Store.
- `proposal.pdf`: A detailed project proposal outlining the objectives, methodology, and expected outcomes of the project.
- `report.pdf`: A comprehensive report documenting the development process, workflow, implementation details, and results of the project.

## Project Objectives
- Develop a console-based shopping application using OOP principles.
- Implement functionalities for product browsing, selection, and cart management.
- Enhance admin capabilities for product management and customer information viewing.
- Integrate a product search feature for improved user experience.

## Implementation Details

### Class Structure
1. **Product Class**: Represents individual products with attributes like name and price.
2. **Category Class**: Represents product categories containing multiple products. Includes methods for adding, editing, deleting, and displaying products.
3. **Store Class**: Manages all categories and overall operations. Includes methods for displaying categories, selecting products, handling admin operations, and managing customer interactions.

### Key Functionalities
#### Product Management
- **Add Product**: Admins can add new products to categories.
- **Edit Product**: Admins can edit existing products in categories.
- **Delete Product**: Admins can delete products from categories.

#### Customer Operations
- **Browse Categories**: Customers can browse different product categories.
- **Select Products**: Customers can select products from categories and add them to their cart.
- **Manage Cart**: The application calculates the total bill for selected products.
- **Save Delivery Info**: Customers enter their details, which are saved to a file for order processing.

#### Admin Interface
- **Authenticate Admin**: Admins authenticate with a password to access admin functionalities.
- **View Customer Information**: Admins can view saved customer information.
- **Change Password**: Admins can change their password after answering a security question.

#### Additional Features
- **Loading Screen**: A loading screen animation for enhanced user experience.
- **Search Product**: Customers can search for products by name within categories.

## Workflow
1. **Initialization**: The store initializes categories and products, displaying a loading screen to the user.
2. **User Access Selection**: Users choose between customer and admin access. Admins authenticate to access the admin menu.
3. **Product Browsing and Selection**: Customers browse categories, select products, and add them to their cart. They can also search for products by name.
4. **Checkout**: Customers enter their details and confirm their purchase.
5. **Admin Operations**: Admins manage products and view customer information through a secure admin interface.

## Advancements Over Previous Project
- **Object-Oriented Design**: Improved code structure and maintainability using classes for `Product`, `Category`, and `Store`.
- **Admin Interface**: Enhanced capabilities for product management and customer information viewing.
- **Search Functionality**: Added product search feature for better user experience.
- **Robust Error Handling**: Improved exception handling for input validation and file operations.

## Future Work
- **Graphical User Interface (GUI)**: Transition from a console-based to a GUI-based application.
- **Real-time Inventory Management**: Implement real-time inventory tracking and management.
- **Payment Integration**: Add secure payment processing functionalities.
- **Multi-user Support**: Extend the application to support concurrent users with real-time updates.

## Conclusion
The Advanced Console-Based C++ Store project successfully implements OOP principles to enhance the functionality, structure, and maintainability of a console-based shopping application. The project serves as both an educational tool and a practical application, demonstrating effective use of C++ for developing robust software systems.
