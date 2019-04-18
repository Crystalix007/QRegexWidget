# Maintainer: Michael Kuc <michaelkuc6 at gmail dot com>
pkgname=QRegexWidget
pkgver=1.0
pkgrel=1
pkgdesc="Simple widget for PCRE regex match and substitution"
arch=("x86_64")
url="https://github.com/Crystalix007/QRegexWidget"
license=('GPL')
depends=('jpcre2')
source=()

prepare() {
	:
}

build() {
	cd ../build
	cmake "-DCMAKE_INSTALL_PREFIX:PATH=${pkgdir}/usr" -GNinja ..
	ninja
}

check() {
	:
}

package() {
	cd ../build
	ninja install
	install -Dm 644 ../QRegexWidget.png     "${pkgdir}/usr/share/pixmaps/QRegexWidget.png"
	install -Dm 644 ../QRegexWidget.desktop "${pkgdir}/usr/share/applications/QRegexWidget.desktop"
}
