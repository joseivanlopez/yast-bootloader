require "yast"

require "bootloader/bootloader_factory"

require "cwm/widget"

Yast.import "UI"
Yast.import "Popup"

module Bootloader
  # Widget to switch between all supported bootloaders
  class LoaderTypeWidget < CWM::ComboBox
    def initialize
      textdomain "bootloader"
    end

    def label
      textdomain "bootloader"

      _("&Boot Loader")
    end

    def init
      self.value = BootloaderFactory.current.name
    end

    def opt
      [:notify]
    end

    def items
      BootloaderFactory.supported_names.map do |name|
        [name, localized_names(name)]
      end
    end

    def localized_names(name)
      names = {
        "grub2"     => _("GRUB2"),
        "grub2-efi" => _("GRUB2 for EFI"),
        # Translators: option in combo box when bootloader is not managed by yast2
        "none"      => _("Not Managed"),
        "default"   => _("Default")
      }

      names[name] or raise "Unknown supported bootloader '#{name}'"
    end

    def handle
      old_bl = BootloaderFactory.current.name
      new_bl = value

      return nil if old_bl == new_bl

      if new_bl == "none"
        # popup - Continue/Cancel
        popup_msg = _(
          "\n" \
          "If you do not install any boot loader, the system\n" \
          "might not start.\n" \
          "\n" \
          "Proceed?\n"
        )

        return :redraw if !Yast::Popup.ContinueCancel(popup_msg)
      end

      BootloaderFactory.current_name = new_bl
      BootloaderFactory.current.propose

      :redraw
    end

    def help
      _(
        "<p><b>Boot Loader Type</b><br>\n" \
          "To select whether to install a boot loader and which bootloader to install,\n" \
          "use <b>Boot Loader</b>.</p>"
      )
    end
  end
end
