#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "NGLFoundation.h"
#import "NGLRegionalOfflineConfig.h"
#import "NGLRegionalOfflineTypes.h"

@class NGLMapView;

NS_ASSUME_NONNULL_BEGIN

NGL_EXPORT
/**
 Legacy object-oriented compatibility surface for Regional Offline.

 New integrations should use the class methods on `NGLRegionalOffline`, which
 own and reuse the same process-wide client. Instances returned by the legacy
 `NGLRegionalOffline/create` methods remain supported for source and binary
 compatibility. Applications should not initialize this class directly.
 */
@interface NGLRegionalOfflineClient : NSObject

@property (nonatomic, readonly, copy) NSDictionary<NSNumber *, NGLRegionalOfflineDownloadProgress *> *downloadProgress;
@property (nonatomic, readonly, copy) NGLRegionalOfflinePreviewBundleImportStatus *previewBundleImportStatus;

#pragma mark - Download page lifecycle

- (void)beginDownloadPageWithOwner:(UIViewController *)owner;
- (void)endDownloadPage;

- (NGLRegionalOfflinePreviewBundleImportStatus *)previewBundleImportStatusSync;

#pragma mark - Download control

- (void)downloadRegionWithId:(NSInteger)regionId
                 clearBefore:(BOOL)clearBefore
           completionHandler:(NGLRegionalOfflineErrorCompletion)completion;

- (void)controlDownloadForRegionId:(NSInteger)regionId action:(NGLRegionalOfflineDownloadAction)action;

#pragma mark - Catalog

/// Regional Offline catalog APIs are available only when TomTom is the active
/// tile server. Asynchronous calls return UnsupportedTileServer otherwise.
- (void)fetchRegionListWithCompletionHandler:(NGLRegionalOfflineRegionListCompletion)completion;
- (void)queryRegionsWithCompletionHandler:(NGLRegionalOfflineRegionSnapshotCompletion)completion;
- (NSArray<NGLRegionalOfflineInstalledRegion *> *)listInstalledRegions;
/// Returns coverage rectangles for all installed regions whose tile databases
/// contain valid `regions.definition.bounds` metadata.
- (NSArray<NGLRegionalOfflineRegionBoundary *> *)installedRegionBoundaries;
- (BOOL)hasInstalledOfflineRegions;
- (NGLRegionalOfflinePreviewResourceStatus *)offlinePreviewResourceStatus;

#pragma mark - Region detail

- (NGLRegionalOfflineRegionDetailResult *)loadOfflineDetailForRegionId:(NSInteger)regionId;
/// Available only when TomTom is the active tile server.
- (void)fetchRegionDetailForRegionId:(NSInteger)regionId
                   completionHandler:(NGLRegionalOfflineRegionDetailCompletion)completion;

#pragma mark - Camera helper

- (BOOL)focusPreviewRegionWithMapView:(NGLMapView *)mapView regionId:(NSInteger)regionId;

#pragma mark - Listeners

- (NGLRegionalOfflineListenerToken *)addDownloadProgressListener:(NGLRegionalOfflineDownloadProgressListener)listener;
- (void)removeDownloadProgressListener:(NGLRegionalOfflineListenerToken *)token;

- (NGLRegionalOfflineListenerToken *)addPreviewBundleImportStatusListener:(NGLRegionalOfflinePreviewBundleImportStatusListener)listener;
- (void)removePreviewBundleImportStatusListener:(NGLRegionalOfflineListenerToken *)token;

@end

NS_ASSUME_NONNULL_END
