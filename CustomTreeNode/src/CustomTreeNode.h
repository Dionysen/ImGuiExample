//
// Created by zhaoys-c on 2025/11/4.
//

#ifndef IMGUIEXAMPLE_CUSTOMTREENODE_H
#define IMGUIEXAMPLE_CUSTOMTREENODE_H

#endif  // IMGUIEXAMPLE_CUSTOMTREENODE_H

#include <imgui.h>
#include <imgui_internal.h>

#include <string>
#include <vector>

namespace ImGui
{
    inline void TreeView()
    {
        const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;
        // const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();

        static ImGuiTableFlags table_flags =
            ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH |
            ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg |
            ImGuiTableFlags_NoBordersInBody;

        static ImGuiTreeNodeFlags tree_node_flags_base =
            ImGuiTreeNodeFlags_SpanAllColumns | ImGuiTreeNodeFlags_DefaultOpen |
            ImGuiTreeNodeFlags_DrawLinesFull;
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanFullWidth",
                             &tree_node_flags_base, ImGuiTreeNodeFlags_SpanFullWidth);
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanLabelWidth",
                             &tree_node_flags_base,
                             ImGuiTreeNodeFlags_SpanLabelWidth);
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanAllColumns",
                             &tree_node_flags_base,
                             ImGuiTreeNodeFlags_SpanAllColumns);
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_LabelSpanAllColumns",
                             &tree_node_flags_base,
                             ImGuiTreeNodeFlags_LabelSpanAllColumns);

        const auto   io        = ImGui::GetIO();
        ImTextureRef my_tex_id = io.Fonts->TexRef;

        if (ImGui::BeginTable("3ways", 3, table_flags))
        {
            // The first column will use the default _WidthStretch when ScrollX is Off
            // and _WidthFixed when ScrollX is On
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
            ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed,
                                    TEXT_BASE_WIDTH * 12.0f);
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed,
                                    TEXT_BASE_WIDTH * 18.0f);
            ImGui::TableHeadersRow();

            // Simple storage to output a dummy file-system.
            struct MyTreeNode
            {
                const char* Name;
                const char* Type;
                int         Size;
                int         ChildIdx;
                int         ChildCount;

                static void DisplayNode(const MyTreeNode* node,
                                        const MyTreeNode* all_nodes)
                {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    const bool is_folder = (node->ChildCount > 0);

                    ImGuiTreeNodeFlags node_flags = tree_node_flags_base;
                    if (node != &all_nodes[0])
                        node_flags &=
                            ~ImGuiTreeNodeFlags_LabelSpanAllColumns;  // Only demonstrate this
                                                                      // on the root node.

                    if (is_folder)
                    {
                        bool open = ImGui::TreeNodeEx(node->Name, node_flags);
                        if ((node_flags & ImGuiTreeNodeFlags_LabelSpanAllColumns | ImGuiTreeNodeFlags_FramePadding) == 0)
                        {
                            ImGui::TableNextColumn();
                            ImGui::TextDisabled("--");
                            ImGui::TableNextColumn();
                            ImGui::TextUnformatted(node->Type);
                        }
                        if (open)
                        {
                            for (int child_n = 0; child_n < node->ChildCount; child_n++)
                                DisplayNode(&all_nodes[node->ChildIdx + child_n], all_nodes);
                            ImGui::TreePop();
                        }
                    }
                    else
                    {
                        ImGui::TreeNodeEx(node->Name,
                                          node_flags | ImGuiTreeNodeFlags_Leaf |
                                              ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanAllColumns | ImGuiTreeNodeFlags_FramePadding);
                        ImGui::TableNextColumn();
                        ImGui::Text("%d", node->Size);
                        ImGui::TableNextColumn();
                        ImGui::TextUnformatted(node->Type);
                    }
                }
            };
            static const MyTreeNode nodes[] = {
                { "Root with Long Name", "Folder", -1, 1, 3 },                      // 0
                { "Music", "Folder", -1, 4, 2 },                                    // 1
                { "Textures", "Folder", -1, 6, 3 },                                 // 2
                { "desktop.ini", "System file", 1024, -1, -1 },                     // 3
                { "File1_a.wav", "Audio file", 123000, -1, -1 },                    // 4
                { "File1_b.wav", "Audio file", 456000, -1, -1 },                    // 5
                { "Image001.png", "Image file", 203128, -1, -1 },                   // 6
                { "Copy of Image001.png", "Image file", 203256, -1, -1 },           // 7
                { "Copy of Image001 (Final2).png", "Image file", 203512, -1, -1 },  // 8
            };

            MyTreeNode::DisplayNode(&nodes[0], nodes);

            ImGui::EndTable();
        }
    }

}  // namespace ImGui
