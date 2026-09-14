#import <Foundation/Foundation.h>

#import "NGLFoundation.h"
#import "NGLRegionalOfflineClient.h"
#import "NGLRegionalOfflineConfig.h"
#import "NGLRegionalOfflineLifecycle.h"
#import "NGLRegionalOfflineStyleCatalog.h"
#import "NGLRegionalOfflineTypes.h"

NS_ASSUME_NONNULL_BEGIN

NGL_EXPORT
/**
 Process-wide facade for configuring, downloading, querying, and displaying
 Regional Offline maps.

 The facade owns one shared internal runtime. New integrations should call
 these class methods directly instead of retaining an
 `NGLRegionalOfflineClient`. Unless documented otherwise, asynchronous
 completions and listener callbacks are delivered on the main thread.
 */
@interface NGLRegionalOffline : NSObject

/**
 Installs Regional Offline process-wide observers and services.

 Calling this method is optional when using the configuration or operation
 methods below, because they install the services lazily. Calling it more than
 once has no effect.
 */
+ (void)install;

/**
 Configures the shared Regional Offline runtime from the active tile server.

 Configure `NGLAccountManager` before calling this method. Regional Offline is
 currently supported only with TomTom. Subsequent Regional Offline operations
 reuse this process-wide configuration and shared runtime.
 */
+ (void)configure;

/**
 Configures or reconfigures the shared Regional Offline runtime.

 The configuration is copied. Reconfiguration preserves the public listener
 registrations while in-flight operations from the previous configuration are
 cancelled or ignored by the internal session guards.

 @param config The configuration to apply. Must not be nil.
 */
+ (void)configureWithConfig:(NGLRegionalOfflineConfig *)config;

/**
 Configures the shared Regional Offline runtime with a custom maps base URL and
 the data source derived from the active tile server.

 @param mapsBaseUrl Base URL for catalog, detail, preview, and package requests.
 */
+ (void)configureWithMapsBaseUrl:(NSString *)mapsBaseUrl;

/// Compatibility API. New integrations should call `configure` and use the
/// class-level operation methods on `NGLRegionalOffline` directly.
/// Creates the shared Regional Offline client. If the active online tile
/// server is not TomTom, the SDK logs a warning and all Regional Offline data,
/// catalog, preview, and download operations remain unavailable until TomTom
/// is active.
+ (NGLRegionalOfflineClient *)create
    __attribute__((deprecated("Use +configure and the class methods on NGLRegionalOffline instead.")));
+ (NGLRegionalOfflineClient *)createWithConfig:(NGLRegionalOfflineConfig *)config
    __attribute__((deprecated("Use +configureWithConfig: and the class methods on NGLRegionalOffline instead.")));
+ (NGLRegionalOfflineClient *)createWithMapsBaseUrl:(NSString *)mapsBaseUrl
    __attribute__((deprecated("Use +configureWithMapsBaseUrl: and the class methods on NGLRegionalOffline instead.")));

#pragma mark - Download state

/**
 Current download progress keyed by region identifier.

 The returned dictionary is an immutable snapshot. It is empty when the active
 tile server does not support Regional Offline.
 */
@property(class, nonatomic, readonly, copy)
    NSDictionary<NSNumber *, NGLRegionalOfflineDownloadProgress *> *downloadProgress;

/**
 Current preview-bundle import state. The returned value is an immutable
 snapshot.
 */
@property(class, nonatomic, readonly, copy)
    NGLRegionalOfflinePreviewBundleImportStatus *previewBundleImportStatus;

#pragma mark - Download page lifecycle

/**
 Marks a download page as visible and starts preparing shared preview
 resources when necessary. The owner is held weakly.

 Calling this method for a different owner closes the previous page lifecycle
 before opening the new one.
 */
+ (void)beginDownloadPageWithOwner:(UIViewController *)owner;

/** Ends the current download-page lifecycle. It is safe to call repeatedly. */
+ (void)endDownloadPage;

/**
 Refreshes marker-backed preview state when called on the main thread and
 returns the latest engine-aware immutable snapshot.
 */
+ (NGLRegionalOfflinePreviewBundleImportStatus *)previewBundleImportStatusSync;

#pragma mark - Download control

/**
 Downloads or updates a regional offline package.

 @param regionId Region identifier from the catalog.
 @param clearBefore Whether an existing installation should be cleared first.
 @param completion Completion delivered on the main thread. It receives an
 error when the operation fails or the current tile server is unsupported.
 */
+ (void)downloadRegionWithId:(NSInteger)regionId
                 clearBefore:(BOOL)clearBefore
           completionHandler:(NGLRegionalOfflineErrorCompletion)completion;

/**
 Pauses, resumes, cancels, or deletes the download or installation associated
 with a region identifier.
 */
+ (void)controlDownloadForRegionId:(NSInteger)regionId
                            action:(NGLRegionalOfflineDownloadAction)action;

#pragma mark - Catalog

/** Fetches the online Regional Offline catalog. Completion runs on main. */
+ (void)fetchRegionListWithCompletionHandler:(NGLRegionalOfflineRegionListCompletion)completion;

/**
 Produces a merged snapshot of the available catalog and locally installed
 regions. Completion runs on the main thread.
 */
+ (void)queryRegionsWithCompletionHandler:(NGLRegionalOfflineRegionSnapshotCompletion)completion;

/** Returns an immutable snapshot of installed regions. */
+ (NSArray<NGLRegionalOfflineInstalledRegion *> *)listInstalledRegions;

/**
 Returns coverage rectangles for installed regions whose tile databases have
 valid `regions.definition.bounds` metadata.
 */
+ (NSArray<NGLRegionalOfflineRegionBoundary *> *)installedRegionBoundaries;

/** Returns whether at least one Regional Offline region is installed. */
+ (BOOL)hasInstalledOfflineRegions;

/** Returns the current locally available preview-resource status. */
+ (NGLRegionalOfflinePreviewResourceStatus *)offlinePreviewResourceStatus;

#pragma mark - Region detail and camera

/** Loads cached detail for a region without performing a network request. */
+ (NGLRegionalOfflineRegionDetailResult *)loadOfflineDetailForRegionId:(NSInteger)regionId;

/** Fetches current detail for a region. Completion runs on the main thread. */
+ (void)fetchRegionDetailForRegionId:(NSInteger)regionId
                   completionHandler:(NGLRegionalOfflineRegionDetailCompletion)completion;

/** Focuses a map on the installed coverage for a region when available. */
+ (BOOL)focusPreviewRegionWithMapView:(NGLMapView *)mapView
                              regionId:(NSInteger)regionId;

#pragma mark - Listeners

/**
 Adds a download-progress listener and publishes its initial snapshot on the
 main thread. When registered from the main thread, the initial callback can
 run before this method returns. Retain the returned token until removal.
 */
+ (NGLRegionalOfflineListenerToken *)addDownloadProgressListener:(NGLRegionalOfflineDownloadProgressListener)listener;

/** Removes a previously registered download-progress listener. */
+ (void)removeDownloadProgressListener:(NGLRegionalOfflineListenerToken *)token;

/**
 Adds a preview-import listener and publishes its initial state on the main
 thread. When registered from the main thread, the initial callback can run
 before this method returns. Retain the returned token until removal.
 */
+ (NGLRegionalOfflineListenerToken *)addPreviewBundleImportStatusListener:(NGLRegionalOfflinePreviewBundleImportStatusListener)listener;

/** Removes a previously registered preview-import listener. */
+ (void)removePreviewBundleImportStatusListener:(NGLRegionalOfflineListenerToken *)token;

#pragma mark - Engine lifecycle and connectivity

/** Refreshes installed Regional Offline resources before a map becomes visible. */
+ (void)onMapViewWillAppear;
/// Forces a Regional Offline engine refresh after a custom account/tile
/// configuration change. Calls to NGLAccountManager tile-server setters trigger
/// this automatically; this method remains available for custom integrations.
+ (void)onTileServerChanged;

/** Refreshes installed tile paths, Preview resources, and offline fallback state. */
+ (void)refreshEngineOnMapResume;

/**
 Performs the map-resume refresh and invokes completion on the main thread.
 Concurrent refresh requests are coalesced without dropping their completions.
 */
+ (void)refreshEngineOnMapResumeWithCompletion:(nullable NGLRegionalOfflineVoidCompletion)completion;

/** Returns the latest network reachability snapshot. */
+ (BOOL)hasInternet;

/**
 Returns whether Regional Offline fallback should currently use local data.
 Always returns `NO` when the active tile server is unsupported.
 */
+ (BOOL)isOfflineForRegionalFallback;
/// Returns YES only when the initialized AccountManager profile is TomTom.
/// MapTiler remains available online, but it has no supported regional-offline
/// package profile in this SDK release.
+ (BOOL)isOfflineMapSupportedForCurrentTileServer;

@end

NS_ASSUME_NONNULL_END
