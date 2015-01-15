//
//  TSPDFDocument.h
//  BrightPay
//
//  Created by Jonathan Mitchell on 12/02/2014.
//  Copyright (c) 2014 Thesaurus Software Limited. All rights reserved.
//

#import <Quartz/Quartz.h>

#import "TSPDFPage.h"

typedef NS_ENUM(NSInteger, TSPageSize) {
    TSPageSizeA4 = 0,
    TSPageSizeA5 = 1,
};

@class TSPDFDocument, TSPDFPage, TSPageBuilder;
@protocol TSPDFDocumentDelegate <NSObject>

@optional

/*!
 
 PDF document will layout page.
 
 */
- (void)pdfDocument:(TSPDFDocument *)document willLayoutPage:(TSPDFPage *)page;

@end

@interface TSPDFDocument : PDFDocument

@property (assign) TSPageSize defaultPageSize;

/*!
 
 Document delegate.
 
 */
@property (weak) id <TSPDFDocumentDelegate, TSPDFPageDelegate, TSPageBuilderDelegate> delegate;

/*!
 
 Layout page items for object based on the contents of the TSPageBuilder xml map URL.
 
 */
- (void)layoutPageItemsForObject:(id)object withMapURL:(NSURL *)url pageIndex:(NSUInteger)pageIndex;

/*!
 
 Insert new page with default size at index within the document.
 
 */
- (TSPDFPage *)insertNewPageAtIndex:(NSInteger)idx;

/*!
 
 Insert new page with specified size at index within the document.
 
 */
- (TSPDFPage *)insertNewPageAtIndex:(NSInteger)idx pageSize:(TSPageSize)pageSize;

/*!
 
 Returns a print operation suitable for printing the PDF document.
 
 */
- (NSPrintOperation *)printOperationWithSettings:(NSDictionary *)printSettings;

@end
