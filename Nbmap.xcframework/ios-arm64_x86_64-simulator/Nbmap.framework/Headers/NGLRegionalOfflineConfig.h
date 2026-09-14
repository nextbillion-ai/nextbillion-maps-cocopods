#import <Foundation/Foundation.h>

#import "NGLFoundation.h"
#import "NGLRegionalOfflineTypes.h"

NS_ASSUME_NONNULL_BEGIN

NGL_EXPORT
@interface NGLRegionalOfflineConfig : NSObject <NSCopying>
@property (nonatomic, readonly, copy) NSString *mapsBaseUrl;
@property (nonatomic, readonly) NSInteger dataSourceId;

FOUNDATION_EXPORT NGL_EXPORT NSString *const NGLRegionalOfflineMapsBaseURLStaticOregonDaotyHK;

- (instancetype)initWithMapsBaseUrl:(NSString *)mapsBaseUrl dataSourceId:(NSInteger)dataSourceId NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Creates the SDK-managed TomTom offline profile. The active online server is
/// read from NGLAccountManager internally; callers must not infer or supply a
/// data-source id from a style URL.
+ (instancetype)fromCurrentTileServer;
+ (instancetype)fromCurrentTileServerWithMapsBaseUrl:(NSString *)mapsBaseUrl;
+ (NSURL *)resourcesCacheDirectory;
@end

NS_ASSUME_NONNULL_END
