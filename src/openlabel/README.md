# OpenLabel Core Library

## Overview

The OpenLabel Core Library is a C++ library designed for creating, modifying, and managing graphical objects and data sources in a scene. The library provides a flexible and modular framework for building applications that require graphical representation and manipulation of data.

## Classes

### Scene

The `Scene` class represents a container for graphical objects and data sources. It provides methods for adding, removing, and modifying the objects and their properties. The `Scene` class is also responsible for handling user events and managing the selection state of graphical objects.

### DataSource

The `DataSource` class represents an abstract data source for a graphical object. Derived classes should implement specific data source types, such as images, audio files, or data streams. Each data source has a unique ID and a set of properties that can be modified.

### GraphicsObject

The `GraphicsObject` class represents an abstract graphical object that can be displayed in a scene. Derived classes should implement specific graphical object types, such as points, lines, or polygons. Each graphical object has a unique ID, a set of properties, and a list of associated data sources.

### Properties

The `Properties` class is a container for key-value pairs, where each key represents a property identifier, and each value is a `QVariant` that can store different data types. The class provides methods for adding, removing, and modifying properties.

### Operation

The `Operation` class is an abstract base class for all undoable and redoable operations performed on a scene. Derived classes should implement specific operation types, such as adding, modifying, or removing graphical objects or data sources.

## Operations

### AddDataSourceOperation

The `AddDataSourceOperation` class is an operation that adds a new data source to a scene. It takes a data source type, a set of properties, and a scene as arguments. The operation can be undone by removing the data source from the scene.

### AddGraphicsOperation

The `AddGraphicsOperation` class is an operation that adds a new graphical object to a scene. It takes a graphics type, a set of properties, a list of associated data source IDs, and a scene as arguments. The operation can be undone by removing the graphical object from the scene.

### ModifyGraphicsOperation

The `ModifyGraphicsOperation` class is an operation that modifies the properties of a graphical object in a scene. It takes a graphics ID, a set of properties, and a scene as arguments. The operation can be undone by swapping the old properties with the new properties.

### RemoveDataSourceOperation

The `RemoveDataSourceOperation` class is an operation that removes a data source from a scene. It takes a data source ID and a scene as arguments. The operation can be undone by adding the data source back to the scene.

### RemoveGraphicsOperation

The `RemoveGraphicsOperation` class is an operation that removes a graphical object from a scene. It takes a graphics ID and a scene as arguments. The operation can be undone by adding the graphical object back to the scene.

## Utility Functions

The library provides several utility functions for converting between enumeration values and strings, such as `dataSourceTypeString()` and `graphicsTypeString()`.

## Notes

This documentation is based on the provided code snippets and may not cover all the aspects of the library. To get a complete understanding of the library's behavior, a full review of the entire project is recommended.