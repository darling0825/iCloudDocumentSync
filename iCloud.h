//
//  iCloud.h
//  iCloud Document Sync
//
//  Created by iRare Media on 12/29/12.
//
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@protocol iCloudDelegate;
@class iCloud;

@interface iCloud : NSObject
{
    __weak id<iCloudDelegate> delegate_;
}

//Public Properties
+(NSMetadataQuery *) query;
+(NSMutableArray *) fileList;
+(NSMutableArray *) previousQueryResults;

//Delegate
@property (nonatomic, weak) id <iCloudDelegate> delegate;

//Private Properties
@property (retain) NSMetadataQuery *query;
@property (retain) NSMutableArray *fileList;
@property (retain) NSMutableArray *previousQueryResults;
@property (retain) NSTimer *updateTimer;

//Sync and Update Docs
+ (BOOL)checkCloudAvailability;
- (void)enumerateCloudDocuments;
+ (void)fileListReceivedWithDelegate:(id<iCloudDelegate>)delegate;
+ (void)uploadDocumentsWithDelegate:(id<iCloudDelegate>)delegate;

//Save, Delete, and Download Docs
+ (void)createDocumentWithData:(NSData *)data withName:(NSString *)name withDelegate:(id<iCloudDelegate>)delegate;
+ (void)removeDocumentWithName:(NSString *)name withDelegate:(id<iCloudDelegate>)delegate;
+ (NSData*)retrieveDocumentDatawithName:(NSString *)name;

@end

@class iCloud;
@protocol iCloudDelegate <NSObject>
@optional
- (void)documentWasDeleted;
- (void)documentWasSaved;
- (void)documentsFinishedUploading;
- (void)documentsStartedUploading;
- (void)documentsStartedDownloading;
- (void)documentsFinishedDownloading;
@required
- (void)fileListChanged:(NSMutableArray *)files;
- (void)cloudError:(NSError *)error;
@end