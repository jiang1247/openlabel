# OpenLabel Project

OpenLabel is a comprehensive, user-friendly graphics editing application that allows users to create, manage, and edit graphic elements in an OpenLabel Scene. The project is organized into several modules, including the core OpenLabel library, the GUI library, and additional utility modules. The application is built using the Qt framework and provides a robust and customizable environment for working with graphics elements.

## Project Structure

The project is organized into the following modules:

1. auxiliary
2. logger
3. permission
4. qtpropertybrowser
5. openlabel
6. gui
7. app

### Auxiliary, Logger, and Permission Modules

The auxiliary, logger, and permission modules provide utility functions, a logging system, and a permission management system, respectively. These modules serve as supporting components for the OpenLabel project.

### QtPropertyBrowser Module

QtPropertyBrowser is a submodule of the open-source [qt-solutions](https://github.com/qtproject/qt-solutions) project. It provides a property management system for the OpenLabel project. We would like to express our gratitude to the QtProject and the contributors for developing and maintaining this valuable resource.

### OpenLabel Core Library

The OpenLabel Core Library is the main library that provides support for creating, managing, and editing graphic elements in an OpenLabel Scene. The library includes:

- **BaseObject, Document, Factory, and Scene**: Core components for managing and working with the OpenLabel document structure and objects within the scene.
- **DataSource**: Handles data sources for objects in the scene, including string data.
- **GraphicsObject**: Base class for graphics objects, with specialized subclasses for specific object types, such as EllipseGraphics and TextGraphics.
- **Operation**: Contains various operation classes for adding, modifying, and removing data sources and graphics objects.
- **Shader**: Provides shader classes for rendering specific graphics objects, such as ellipse and text shaders.
- **Event**: Contains event classes and event listener interfaces for handling different types of events related to data sources, graphics, and scenes.

### OpenLabel GUI Library

The OpenLabel GUI Library is a collection of graphical user interface (GUI) components for creating, managing, and editing graphic elements in an OpenLabel Scene. The library includes:

- **MainWindow**: Serves as the primary interface for the application, containing the entire application structure, including menu bars, toolbars, and dock widgets.
- **EditArea, GraphicsScene, and GraphicsView**: Core components for displaying and interacting with graphics objects in the scene.
- **GraphicsItem**: Represents individual graphics elements in the scene, providing a QGraphicsItem-derived class for managing graphics object interactions.
- **Action**: Contains action classes for various user operations, such as adding graphics objects, creating new documents, opening and saving documents, and removing graphics objects.
- **MouseProxy**: Provides mouse interaction handling classes, such as ResizeHandleItem, SelectedBoxItem, and SelectingBoxItem, for managing graphics object selection and resizing.
- **Property**: Includes a dynamic property management system with property handler and property manager classes for managing properties of graphics objects in the scene.
- **BindingDataSourceDialog, DataListDockWidget, GraphicsListDockWidget, and OperationsDockWidget**: Implements various dialogs and dock widgets for managing data sources, graphics objects, and operations.

### App Module

The app module is the main application entry point and serves as the glue that combines all the other modules to create the OpenLabel graphics editing application. It includes the main entry point and initialization logic.

## Getting Started

To build and run the OpenLabel application, follow these steps:

1. Clone the repository
2. Open the project in Qt Creator
3. Configure the project for your desired build target
4. Build and run the application

By combining these modules, the OpenLabel project provides a comprehensive solution for creating, managing, and editing graphic elements in an OpenLabel Scene. Users can easily interact with graphics objects through the intuitive user interface and can efficiently work with properties, data sources, and operations associated with these objects.

The modular structure of the project allows for easy extensibility and maintenance, ensuring that the application can continue to evolve and adapt to the needs of its users. As a result, OpenLabel is a powerful and versatile graphics editing application that can be used for a wide range of applications, from simple graphic design tasks to more complex visualizations and presentations.

To contribute to the project or report issues, visit the project's GitHub repository and follow the standard procedures for submitting pull requests or reporting issues. We welcome contributions from the community and are committed to maintaining and improving the OpenLabel project for the benefit of all users.

Thank you for your interest in the OpenLabel project, and we hope you find the application useful and enjoyable to use!