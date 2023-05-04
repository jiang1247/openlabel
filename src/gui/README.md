# OpenLabel GUI Library

The OpenLabel GUI Library is a collection of graphical user interface (GUI) components for creating, managing, and editing graphic elements in an OpenLabel Scene. The library is built using the Qt framework and provides support for handling various properties such as font, color, and other visual attributes, as well as offering a comprehensive graphics editing environment.

## Features

- Create and manipulate graphics elements in an OpenLabel Scene
- Display and edit properties of graphic elements
- Support for handling multiple types of graphics properties through a dynamic property management system
- Font property handler for managing font-related properties
- MouseProxy for handling mouse events and interactions
- Action management for undo, redo, and other operations
- MainWindow as the primary interface containing the entire application structure
- GraphicsItem, GraphicsScene, and GraphicsView for a complete graphics editing experience

## Components

### GraphicsItem

- Represents individual graphic elements in the OpenLabel Scene
- Encapsulates properties and methods for rendering and interacting with the graphic elements

### GraphicsScene

- Manages and displays the collection of GraphicsItems
- Provides methods for adding, removing, and manipulating graphics elements in the scene

### GraphicsView

- Displays the content of a GraphicsScene
- Handles user interactions such as zooming, panning, and selecting graphic elements

### MouseProxy

- Handles mouse events and interactions with the graphic elements in the OpenLabel Scene
- Implements features such as zooming, panning, and selecting graphic elements

### Property

- Provides a dynamic property management system that supports different types of graphic properties
- Includes property handlers for various property types, including font properties
- GraphicsPropertyDockWidget serves as a dockable widget to display and edit properties of selected graphic elements

### Action

- Manages undo, redo, and other operations in the OpenLabel Scene
- Allows users to perform various actions on the graphic elements

### MainWindow

- Serves as the main window and primary interface for the application
- Contains the entire structure of the application, including menu items, toolbars, and dockable widgets

By incorporating these components, the OpenLabel GUI Library offers a comprehensive and user-friendly graphics editing environment for managing and editing graphic elements in an OpenLabel Scene. Users can integrate this library into their applications to build customized graphical interfaces tailored to their specific needs.