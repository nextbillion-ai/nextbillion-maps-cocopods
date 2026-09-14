#import <Foundation/Foundation.h>

#import "NGLFoundation.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Error domain

FOUNDATION_EXPORT NGL_EXPORT NSErrorDomain const NGLRegionalOfflineErrorDomain;
FOUNDATION_EXPORT NGL_EXPORT NSString *const NGLRegionalOfflineErrorURLKey;
FOUNDATION_EXPORT NGL_EXPORT NSString *const NGLRegionalOfflineErrorHTTPStatusCodeKey;
FOUNDATION_EXPORT NGL_EXPORT NSString *const NGLRegionalOfflineErrorPackageNameKey;
/// JSON path of a malformed response value, for example `$.results[1]`.
FOUNDATION_EXPORT NGL_EXPORT NSString *const NGLRegionalOfflineErrorJSONPathKey;
/// Versioned Preview SQLite path that failed to open in the native engine.
FOUNDATION_EXPORT NGL_EXPORT NSString *const NGLRegionalOfflineErrorPreviewDatabasePathKey;
/// Additional errors encountered while restoring the previous Preview generation.
FOUNDATION_EXPORT NGL_EXPORT NSString *const NGLRegionalOfflineErrorRollbackErrorsKey;

typedef NS_ERROR_ENUM(NGLRegionalOfflineErrorDomain, NGLRegionalOfflineErrorCode) {
    NGLRegionalOfflineErrorCodeNetwork = 1,
    NGLRegionalOfflineErrorCodeStorage,
    NGLRegionalOfflineErrorCodeInvalidRegion,
    NGLRegionalOfflineErrorCodePreviewNotReady,
    NGLRegionalOfflineErrorCodeStyleNotCached,
    NGLRegionalOfflineErrorCodeNoInstalledRegions,
    NGLRegionalOfflineErrorCodeCancelled,
    NGLRegionalOfflineErrorCodeUnknown,
    /// The device cannot currently reach the network.
    NGLRegionalOfflineErrorCodeNetworkUnavailable,
    /// The request exceeded its timeout interval.
    NGLRegionalOfflineErrorCodeRequestTimedOut,
    /// The server returned a non-success HTTP status code.
    NGLRegionalOfflineErrorCodeHTTPStatus,
    /// The server response or region metadata is malformed.
    NGLRegionalOfflineErrorCodeInvalidResponse,
    /// A local file could not be created, read, written, moved, or removed.
    NGLRegionalOfflineErrorCodeFileSystem,
    /// The device does not have enough free storage.
    NGLRegionalOfflineErrorCodeInsufficientStorage,
    /// The downloaded package is truncated, corrupt, or has an unsupported format.
    NGLRegionalOfflineErrorCodeInvalidPackage,
    /// A compressed package could not be decompressed.
    NGLRegionalOfflineErrorCodePackageDecompression,
    /// A downloaded package could not be installed into offline storage.
    NGLRegionalOfflineErrorCodePackageInstallation,
    /// A download for the same data source and region is already queued, running, or paused.
    NGLRegionalOfflineErrorCodeDownloadAlreadyActive,
    /// The validated Preview SQLite file could not be opened by the native map engine.
    NGLRegionalOfflineErrorCodePreviewDatabaseOpen,
    /// Preview activation failed and restoring the previous generation was incomplete.
    NGLRegionalOfflineErrorCodePreviewRollbackFailed,
    /// The active online tile-server profile has no compatible offline package source.
    NGLRegionalOfflineErrorCodeUnsupportedTileServer,
};

#pragma mark - Tile server data source

typedef NS_ENUM(NSInteger, NGLRegionalOfflineTileServerDataSource) {
    NGLRegionalOfflineTileServerDataSourceTomTom = 1,
    NGLRegionalOfflineTileServerDataSourceNbMapTile = 2,
};

#pragma mark - Download state / action

typedef NS_ENUM(NSInteger, NGLRegionalOfflineDownloadState) {
    NGLRegionalOfflineDownloadStateQueued = 0,
    /// Regional packages are installed; the shared Preview Bundle is still
    /// downloading, validating, or being applied to the map engine.
    NGLRegionalOfflineDownloadStatePreparingOfflineDisplay,
    NGLRegionalOfflineDownloadStateDownloadingPackage,
    NGLRegionalOfflineDownloadStatePausedUser,
    NGLRegionalOfflineDownloadStatePausedNetwork,
    NGLRegionalOfflineDownloadStateFailedStorage,
    NGLRegionalOfflineDownloadStateFailed,
    /// Regional packages and all required Preview resources are ready and have
    /// been applied to the map engine. Only this state reports 100 percent.
    NGLRegionalOfflineDownloadStateCompleted,
    NGLRegionalOfflineDownloadStateCancelled,
};

typedef NS_ENUM(NSInteger, NGLRegionalOfflineDownloadAction) {
    NGLRegionalOfflineDownloadActionPause = 0,
    NGLRegionalOfflineDownloadActionResume,
    NGLRegionalOfflineDownloadActionCancel,
    NGLRegionalOfflineDownloadActionDelete,
};

#pragma mark - Catalog / install models

NGL_EXPORT
@interface NGLRegionalOfflineRegionListItem : NSObject <NSCopying>
@property (nonatomic, readonly) NSInteger regionId;
@property (nonatomic, readonly, copy) NSString *name;
@property (nonatomic, readonly, copy) NSString *adminL0;
@property (nonatomic, readonly, copy) NSString *adminL1;
@property (nonatomic, readonly, copy) NSString *adminL3;
@property (nonatomic, readonly, copy, nullable) NSString *version;
@property (nonatomic, readonly) int64_t totalSize;
@property (nonatomic, readonly) NSInteger tileCount;
@property (nonatomic, readonly, nullable) NSNumber *timestamp;
- (instancetype)initWithRegionId:(NSInteger)regionId
                            name:(NSString *)name
                         adminL0:(NSString *)adminL0
                         adminL1:(NSString *)adminL1
                         adminL3:(NSString *)adminL3
                         version:(nullable NSString *)version
                       totalSize:(int64_t)totalSize
                       tileCount:(NSInteger)tileCount
                       timestamp:(nullable NSNumber *)timestamp NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

typedef NGLRegionalOfflineRegionListItem NGLRegionalOfflineCatalogItem;

NGL_EXPORT
@interface NGLRegionalOfflineTarInfo : NSObject <NSCopying>
@property (nonatomic, readonly, copy) NSString *tarName;
@property (nonatomic, readonly, copy) NSString *version;
@property (nonatomic, readonly) int64_t tarSize;
@property (nonatomic, readonly, nullable) NSNumber *timestamp;
@property (nonatomic, readonly) NSInteger minZoom;
@property (nonatomic, readonly) NSInteger maxZoom;
@property (nonatomic, readonly, copy) NSString *stem;
- (instancetype)initWithTarName:(NSString *)tarName
                        version:(NSString *)version
                        tarSize:(int64_t)tarSize
                      timestamp:(nullable NSNumber *)timestamp
                        minZoom:(NSInteger)minZoom
                        maxZoom:(NSInteger)maxZoom NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NGL_EXPORT
@interface NGLRegionalOfflineRegionDetail : NSObject <NSCopying>
@property (nonatomic, readonly) NSInteger regionId;
@property (nonatomic, readonly, copy, nullable) NSString *version;
@property (nonatomic, readonly, copy, nullable) NSString *country;
@property (nonatomic, readonly, copy, nullable) NSString *adminL1;
@property (nonatomic, readonly, copy, nullable) NSString *adminL2;
@property (nonatomic, readonly, copy, nullable) NSString *adminL3;
@property (nonatomic, readonly, nullable) NSNumber *timestamp;
@property (nonatomic, readonly) int64_t totalSize;
@property (nonatomic, readonly, copy) NSArray<NGLRegionalOfflineTarInfo *> *tarList;
- (instancetype)initWithRegionId:(NSInteger)regionId
                         version:(nullable NSString *)version
                         country:(nullable NSString *)country
                         adminL1:(nullable NSString *)adminL1
                         adminL2:(nullable NSString *)adminL2
                         adminL3:(nullable NSString *)adminL3
                       timestamp:(nullable NSNumber *)timestamp
                       totalSize:(int64_t)totalSize
                         tarList:(NSArray<NGLRegionalOfflineTarInfo *> *)tarList NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NGL_EXPORT
@interface NGLRegionalOfflineInstalledRegionSummary : NSObject <NSCopying>
@property (nonatomic, readonly) NSInteger regionId;
@property (nonatomic, readonly, copy) NSString *displayName;
@property (nonatomic, readonly) NSInteger packageCount;
@property (nonatomic, readonly) int64_t totalBytes;
@property (nonatomic, readonly, copy, nullable) NSString *regionVersion;
@property (nonatomic, readonly) BOOL allTarsOk;
@property (nonatomic, readonly) NSInteger dataSourceId;
@property (nonatomic, readonly, copy) NSString *dataSourceLabel;
- (instancetype)initWithRegionId:(NSInteger)regionId
                     displayName:(NSString *)displayName
                    packageCount:(NSInteger)packageCount
                      totalBytes:(int64_t)totalBytes
                   regionVersion:(nullable NSString *)regionVersion
                       allTarsOk:(BOOL)allTarsOk
                    dataSourceId:(NSInteger)dataSourceId
                 dataSourceLabel:(NSString *)dataSourceLabel NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

typedef NGLRegionalOfflineInstalledRegionSummary NGLRegionalOfflineInstalledRegion;

/// Geographic coverage bounds read from an installed regional-offline tile database.
///
/// The bounds describe the downloaded tile coverage rectangle. They are not an
/// administrative boundary polygon.
NGL_EXPORT
@interface NGLRegionalOfflineRegionBoundary : NSObject <NSCopying>
@property (nonatomic, readonly) NSInteger regionId;
@property (nonatomic, readonly, copy) NSString *displayName;
@property (nonatomic, readonly) double southLatitude;
@property (nonatomic, readonly) double westLongitude;
@property (nonatomic, readonly) double northLatitude;
@property (nonatomic, readonly) double eastLongitude;
- (instancetype)initWithRegionId:(NSInteger)regionId
                     displayName:(NSString *)displayName
                   southLatitude:(double)southLatitude
                   westLongitude:(double)westLongitude
                   northLatitude:(double)northLatitude
                   eastLongitude:(double)eastLongitude NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NGL_EXPORT
@interface NGLRegionalOfflineDownloadProgress : NSObject <NSCopying>
@property (nonatomic, readonly) NSInteger regionId;
@property (nonatomic, readonly) NGLRegionalOfflineDownloadState state;
@property (nonatomic, readonly) int64_t downloadedBytes;
@property (nonatomic, readonly) int64_t totalBytes;
@property (nonatomic, readonly, copy, nullable) NSString *currentPackageName;
/// Structured failure detail. This can be nonnull while waiting for Preview
/// retry as well as in a terminal failure state. Inspect domain, code, and
/// userInfo for the exact reason.
@property (nonatomic, readonly, copy, nullable) NSError *error;
/// Compatibility shortcut for error.localizedDescription.
@property (nonatomic, readonly, copy, nullable) NSString *errorMessage;
@property (nonatomic, readonly) NSInteger percent;
- (instancetype)initWithRegionId:(NSInteger)regionId
                           state:(NGLRegionalOfflineDownloadState)state
                 downloadedBytes:(int64_t)downloadedBytes
                      totalBytes:(int64_t)totalBytes
               currentPackageName:(nullable NSString *)currentPackageName
                    errorMessage:(nullable NSString *)errorMessage
                         percent:(NSInteger)percent;
- (instancetype)initWithRegionId:(NSInteger)regionId
                           state:(NGLRegionalOfflineDownloadState)state
                 downloadedBytes:(int64_t)downloadedBytes
                      totalBytes:(int64_t)totalBytes
              currentPackageName:(nullable NSString *)currentPackageName
                           error:(nullable NSError *)error
                    errorMessage:(nullable NSString *)errorMessage
                         percent:(NSInteger)percent NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NGL_EXPORT
@interface NGLRegionalOfflineRegionSnapshot : NSObject <NSCopying>
@property (nonatomic, readonly, copy) NSArray<NGLRegionalOfflineCatalogItem *> *catalog;
@property (nonatomic, readonly, copy) NSArray<NGLRegionalOfflineInstalledRegion *> *installed;
@property (nonatomic, readonly) BOOL ambientReady;
@property (nonatomic, readonly) BOOL glyphsReady;
@property (nonatomic, readonly) BOOL stylesReady;
- (instancetype)initWithCatalog:(NSArray<NGLRegionalOfflineCatalogItem *> *)catalog
                      installed:(NSArray<NGLRegionalOfflineInstalledRegion *> *)installed
                   ambientReady:(BOOL)ambientReady
                    glyphsReady:(BOOL)glyphsReady
                    stylesReady:(BOOL)stylesReady NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NGL_EXPORT
@interface NGLRegionalOfflinePreviewBundleImportStatus : NSObject <NSCopying>
@property (nonatomic, readonly) BOOL previewBundleReady;
@property (nonatomic, readonly) BOOL ensuring;
@property (nonatomic, readonly) BOOL waitingForNetwork;
@property (nonatomic, readonly, copy, nullable) NSString *lastErrorCode;
@property (nonatomic, readonly, copy, nullable) NSString *lastErrorMessage;
@property (nonatomic, readonly) BOOL recoverable;
+ (instancetype)idleStatus;
+ (instancetype)readyStatus;
- (instancetype)initWithPreviewBundleReady:(BOOL)previewBundleReady
                                   ensuring:(BOOL)ensuring
                         waitingForNetwork:(BOOL)waitingForNetwork
                              lastErrorCode:(nullable NSString *)lastErrorCode
                           lastErrorMessage:(nullable NSString *)lastErrorMessage
                                recoverable:(BOOL)recoverable NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NGL_EXPORT
@interface NGLRegionalOfflinePreviewResourceStatus : NSObject <NSCopying>
@property (nonatomic, readonly) BOOL previewBundleReady;
@property (nonatomic, readonly) BOOL styleJsonCached;
@property (nonatomic, readonly) BOOL spritesReady;
@property (nonatomic, readonly) BOOL tileJsonReady;
@property (nonatomic, readonly, copy) NSArray<NSString *> *cachedPreviewStyleNames;
- (instancetype)initWithPreviewBundleReady:(BOOL)previewBundleReady
                            styleJsonCached:(BOOL)styleJsonCached
                              spritesReady:(BOOL)spritesReady
                              tileJsonReady:(BOOL)tileJsonReady
                   cachedPreviewStyleNames:(NSArray<NSString *> *)cachedPreviewStyleNames NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NGL_EXPORT
@interface NGLRegionalOfflineRegionDetailResult : NSObject
@property (nonatomic, readonly, nullable) NGLRegionalOfflineRegionDetail *detail;
@property (nonatomic, readonly, copy, nullable) NSString *detailJson;
- (instancetype)initWithDetail:(nullable NGLRegionalOfflineRegionDetail *)detail
                    detailJson:(nullable NSString *)detailJson NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

#pragma mark - Listener tokens

NGL_EXPORT
@interface NGLRegionalOfflineListenerToken : NSObject
@end

#pragma mark - Completion typedefs

typedef void (^NGLRegionalOfflineVoidCompletion)(void);
typedef void (^NGLRegionalOfflineErrorCompletion)(NSError *_Nullable error);
typedef void (^NGLRegionalOfflineRegionListCompletion)(NSArray<NGLRegionalOfflineCatalogItem *> *_Nullable items,
                                                       NSError *_Nullable error);
typedef void (^NGLRegionalOfflineRegionSnapshotCompletion)(NGLRegionalOfflineRegionSnapshot *_Nullable snapshot,
                                                           NSError *_Nullable error);
typedef void (^NGLRegionalOfflineRegionDetailCompletion)(NGLRegionalOfflineRegionDetail *_Nullable detail,
                                                           NSString *_Nullable detailJson,
                                                           NSError *_Nullable error);
typedef void (^NGLRegionalOfflineDownloadProgressListener)(NSDictionary<NSNumber *, NGLRegionalOfflineDownloadProgress *> *progressByRegionId);
typedef void (^NGLRegionalOfflinePreviewBundleImportStatusListener)(NGLRegionalOfflinePreviewBundleImportStatus *status);

#pragma mark - Error helpers

FOUNDATION_EXPORT NGL_EXPORT NSError *_Nullable NGLRegionalOfflineError(NGLRegionalOfflineErrorCode code, NSString *message);
FOUNDATION_EXPORT NGL_EXPORT NSString *NGLRegionalOfflineDownloadStateLabel(NGLRegionalOfflineDownloadState state);
FOUNDATION_EXPORT NGL_EXPORT void NGLRegionalOfflineRunOnMain(void (^block)(void));

#pragma mark - Version helpers

/// Compares dotted numeric/SemVer-style region versions without converting
/// them to fixed-width integers. Missing versions sort before non-empty ones.
FOUNDATION_EXPORT NGL_EXPORT NSComparisonResult
NGLRegionalOfflineCompareVersions(NSString *_Nullable lhs,
                                  NSString *_Nullable rhs);
FOUNDATION_EXPORT NGL_EXPORT BOOL
NGLRegionalOfflineVersionIsNewer(NSString *_Nullable remote,
                                 NSString *_Nullable local);

NS_ASSUME_NONNULL_END
