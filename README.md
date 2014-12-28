Cocoa PDF Page Builder
======================

PDFPageBuilder is a Cocoa framework that provides a simple PDF page templating system. A keyed data object is mapped onto a PDF page based on an XML template file.

The included demo app shows how to accurately position text and images on a pre-existing PDF document. It also illustrates how to render multiple objects to a single PDF page and how to generate multiple pages from multiple objects.

![PDFPageBuilder image](./Documents/PageBuilderDemoApp.png?raw=true )

Usage
=====

PDFPageBuilder has no external dependencies so all that is required is to link the framework to your app. Note that the framework installation directory is defined as `@rpath` so the app's Runpath Search Paths build setting will need to be set to `@executable_path/../Frameworks`.

The following method lays out a given object using a url that defines the XML mapping file to a given PDF document page index :

    TSPDFDocument -(void)layoutPageItemsForObject:(id)object withMapURL:(NSURL *)url pageIndex:(NSUInteger)pageIndex

The object must be KVC compliant for the keys defined in the XML mapping file. The mapping file specifies the position and styling to be be applied to the object key values.

PDFPageBuilder has no dependency on PDFView. All rendered objects become part of the PDFDocument and will be saved and printed as such.

Requires 64 bit ARC. 

Box Model
=========

PDFPageBuilder uses a top left based co-ordinate system that corresponds to an NSView flipped context. All dimensions are in mm from the top left hand page corner. A scaling factor can be defined for use in cases where the map file contains dimensions in non mm units. FontSizes also default to mm.

Each page item requires X and Y values denoting the item insertion point. In many cases an explicit box Width and Height will be defined. Text items wrap within the box and may be justified both horizontally and vertically.

If no explicit Width is supplied then the box defaults to the page width. If no explicit Height is defined then the box height will default to the laid out size of the content.

Box positioning issues can be debugged by setting `PDFPageBuilder -highlightPageItemContainerRects = YES` to outline the box rect following layout.

Rendering
=========

A page item is rendered based on the values of geometry and styling properties defined in the mapping file. Properties can be pushed on to a stack to be applied to all subsequent items or defined as attributes in which case they apply to just the defining element.

Normally items are added to the page by loading a mapping file. However items can be added directly to the pageBuilder object. This approach is illustrated in the demo app.

XML Map File Format
==========

Usage of all that is described below is illustrated in the [demo map XML file](./PageBuilderDemo/Demo-A4.map.xml). It is probably easiest to read the XML file directly in order to figure out the syntax outlined below.

The map file defines key paths which are used to access object properties and provides position and styling information to apply to the object property when it is rendered into the PDF page. Both textual and image items can be rendered.

XML Map File Keys
---------------------

Object keys are defined with the XML text like so:

    {KeyName}
	{KeyName.Support.Paths with spaces}

Then when the XML is loaded and parsed for a given `object` the key expressions are replaced by the value of `[object valueForKey:@"KeyName"]`.

XML Map File Elements
---------------------

The XML file supports the following elements:

__Condition__ - A conditional test that supports boolean AND, OR and ! expressions and True / False child elements.

		<Condition Expression="IsConditionA OR IsConditionB">
			<True>
				<Run Foreground="redColor"> and {CondA} or {CondB} is true</Run>
			</True>
		</Condition>



__Constant__ - A simple constant value that the client can use to assist with layout.

		<Constant Name="NumberPerPage" Value="2" />

__False__ - The elements content will be rendered if the enclosing Condition evaluates to false.

		<Condition Expression="ShowCredits">
			<False>
				<Text X="159.146" Y="134.733" Width="41.355" Height="5.625" BorderBackground="ffffff"> </Text>
			</False>
		</Condition>

__ForEach__ - Iterate over a collection object based on the value of the element attributes.

		<ForEach Enumerable="Box4Details" Text.Y="98.491" Text.YSpacing="0">
			<Text X="12" Width="40" Foreground="404142">{Key}</Text>
			<Text X="12" Width="57.667" TextAlignment="Right">{Value}</Text>
		</ForEach>

__Image__ - Insert an image item based on the value of the element attributes. 

		<Image Source="{Logo}" X="138.333" Y="13" Width="61.667" Height="10.045" />


__LineBreak__ - Inserts a line break.

		<LineBreak />
		<Run>{Box6Sub3Content}</Run>

__Pop__ - Pop the last value from the named property stack.

		<Pop Property="FontSize" />

__Push__ - Push a value onto the named property stack.

		<Push Property="FontFamily" Value="Helvetica" />

__Run__ - Enables the concatenation of separate text segments within an enclosing Text element.

		<Text X="10" Y="10" Width="190" Height="16.045" FontSize="16">
			<Run FontSize="18" Foreground="blueColor">{AppName} </Run>
		</Text>

__Text__ - Insert a text item based on the value of the element attributes.

		<Text X="76.167" Width="57.667" TextAlignment="Right" FontFamily="Arial">£{Value:N02}</Text>

__True__ - The elements content will be rendered if the enclosing Condition expression evaluates to true.

		<Condition Expression="IsLogoIncluded">
			<True>
				<Image Source="{Logo}" X="138.333" Y="13" Width="61.667" Height="10.045" />
			</True>
			<False>
				<Text X="10" Y="10" Width="190" Height="16.045">
					<Run FontWeight="Bold">{AppName}</Run>
				</Text>
			</False>
		</Condition>

XML Map File Attributes
---------------------

The XML file supports the following element attributes:

* __BorderBackground__ - Box background colour : hex RGB (P).

* __Enumerable__ - A collection object to be enumerated over.

* __Expression__ - A simple Boolean expression used to evaluate a Condition element : AND, OR and !.

* __FontSize__ - Font size (P).

* __FontFamily__ - Font family name (P).

* __FontStyle__ - Font style : Italic (P).

* __FontWeight__ - Font weight : Bold (P).

* __Foreground__ - Foreground colour : hex RGB (P).

* __Height__ - Box Height.

* __Key__ - An enumerable Key.

* __Name__ - Identifies a named constant.

* __Property__ - An attribute name to be used when pushing or popping.

* __Source__ - An image source.

* __TextAlignment__ - Alignment with a box rect : Left, Center or Right (P)

* __TextPadding__ - Box padding : 4 csv values (left, top, right, bottom) (P).

* __TextVerticalAlignment__ - Alignment with a box rect : Top, Center or Bottom (P).

* __Text.Y__ - An initial enumerated text Y position.

* __Text.YSpacing__ - Enumerated text spacing.

* __Value__ - A Value.

* __Width__ - Box width.

* __X__ - X co-ordinate position.

* __Y__ - Y Co-ordinate position.






(P) Values can be pushed as properties for these attributes.
 
Delegate methods
================

A number of delegate methods are provided to assist with customising the rendering process. See the demo app for insight.

Credits
=======
PDFPageBuilder is a Cocoa port of a WPF FixedDocument solution design and implemented by Ross Webster. This explains the XAML like nature of the XML mapping file.

Licence
=======

MIT



